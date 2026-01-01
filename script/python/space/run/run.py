#!/usr/bin/env python3

import os
import subprocess as spc
import argparse
import sys
import shlex
from pathlib import Path
from typing import List, Optional

class CompilerRunner:
    def __init__(self, flags: str = ""):
        self.is_posix = os.name == "posix"
        self.output_files: List[Path] = []
        # Clean flags extra '' and ""
        clean_flags = flags.strip().strip('"').strip("'")
        self.extra_flags = shlex.split(clean_flags) if clean_flags else []

    def get_executable_path(self, source_path: Path) -> Path:
        name = source_path.stem
        # Windows: .exe, POSIX: .out
        return Path(f"{name}.exe" if not self.is_posix else f"./{name}.out")

    def run_command(self, cmd: List[str], use_shell: bool = False) -> bool:
        try:
            result = spc.run(cmd, check=False, shell=use_shell)
            return result.returncode == 0
        except FileNotFoundError:
            print(f"Error: Command '{cmd[0]}' not found.")
            return False

    def compile_and_run(self, files: List[str], multi: bool = False):
        if not files: return
        file_paths = [Path(f) for f in files]
        
        if multi:
            self._handle_multi_compile(file_paths)
        else:
            for fp in file_paths:
                self._handle_single_file(fp)

    # --- Cargo Utilities ---
    def _find_cargo_toml(self, start_path: Path) -> Optional[Path]:
        """Walk up to find Cargo.toml"""
        current = start_path.absolute()
        if current.is_file():
            current = current.parent
            
        for _ in range(3): # Check up to 3 levels up
            toml = current / "Cargo.toml"
            if toml.exists():
                return toml
            current = current.parent
        return None

    def _get_cargo_package_name(self, toml_path: Path) -> Optional[str]:
        """Simple parsing to get package name from Cargo.toml"""
        try:
            with open(toml_path, 'r', encoding='utf-8') as f:
                in_package = False
                for line in f:
                    line = line.strip()
                    if line == "[package]":
                        in_package = True
                        continue
                    if line.startswith("[") and line.endswith("]"):
                        in_package = False
                    
                    if in_package and line.startswith("name"):
                        # name = "project_name"
                        parts = line.split('=')
                        if len(parts) >= 2:
                            return parts[1].strip().strip('"').strip("'")
        except Exception:
            pass
        return None

    def run_cargo_mode(self, toml_path: Path = None):
        """Handle cargo execution logic: run -q OR build && run"""
        # If path not provided, assume current dir
        if not toml_path:
            toml_path = Path("Cargo.toml")

        is_release = "--release" in self.extra_flags
        
        if is_release:
            # Case: Build Release -> Run Binary
            print("Building release...")
            build_cmd = ["cargo", "build"] + self.extra_flags
            if not self.run_command(build_cmd):
                return
            
            pkg_name = self._get_cargo_package_name(toml_path)
            if not pkg_name:
                print("Error: Could not parse package name from Cargo.toml")
                return

            bin_name = f"{pkg_name}.exe" if not self.is_posix else pkg_name
            target_bin = toml_path.parent / "target" / "release" / bin_name
            
            if target_bin.exists():
                self._execute_binary(target_bin)
            else:
                print(f"Error: Binary not found at {target_bin}")
        else:
            # Case: Default Run Quiet
            # Note: -q comes before --flags to ensure cargo itself is quiet
            cmd = ["cargo", "run", "-q"] + self.extra_flags
            self.run_command(cmd)

    def _handle_rust_execution(self, fp: Path):
        cargo_toml = self._find_cargo_toml(fp)
        
        if cargo_toml:
            print(f"Found Cargo project: {cargo_toml.parent.name}")
            self.run_cargo_mode(cargo_toml)
        else:
            # --- Rustc Mode (Single File) ---
            out_name = self.get_executable_path(fp)
            cmd = ["rustc", str(fp), "-o", str(out_name)] + self.extra_flags
            if self.run_command(cmd):
                self.output_files.append(out_name)
                self._execute_binary(out_name)

    def _handle_single_file(self, fp: Path):
        ext = fp.suffix.lower()
        out_name = self.get_executable_path(fp)

        match ext:
            case ".py":
                prog = "python" if not self.is_posix else "python3"
                spc.run([prog, str(fp)])
            case ".java":
                spc.run(["java", str(fp)])
            case ".go":
                spc.run(["go", "run", str(fp)])
            case ".rs":
                self._handle_rust_execution(fp)
            case ".lua":
                check_cmd = "where" if not self.is_posix else "command -v"
                is_lua = spc.run(f"{check_cmd} lua", shell=True, capture_output=True).returncode == 0
                prog = "lua" if is_lua else "luajit"
                spc.run([prog, str(fp)])
            case ".js":
                spc.run(["node", str(fp)])
            case _ if ext in ('.c', '.cpp', '.cc'):
                compiler = "gcc" if ext == ".c" else "g++"
                cmd = [compiler] + self.extra_flags + [str(fp), "-o", str(out_name)]
                if self.run_command(cmd):
                    self.output_files.append(out_name)
                    self._execute_binary(out_name)
            case _:
                print(f"Unsupported extension: {ext}")

    def _handle_multi_compile(self, paths: List[Path]):
        sources = [p for p in paths if p.suffix in ('.c', '.cpp', '.cc')]
        headers = [p for p in paths if p.suffix in ('.h', '.hpp')]
        if not sources: return

        main_source = sources[0]
        ext = main_source.suffix.lower()

        if ext in ('.c', '.cpp', '.cc'):
            compiler = "gcc" if ext == ".c" else "g++"
            out_name = self.get_executable_path(main_source)

            cmd = [compiler] + self.extra_flags + [str(s) for s in sources]
            include_dirs = {str(h.parent) for h in headers}
            for d in include_dirs:
                cmd.append(f"-I{d}")
            cmd += ["-o", str(out_name)]

            if self.run_command(cmd):
                self.output_files.append(out_name)
                self._execute_binary(out_name)
        else:
            print(f"Unsupported extension for multi: {ext}")

    def _execute_binary(self, bin_path: Path):
        target = str(bin_path) if self.is_posix else str(bin_path.absolute())
        # Ensure ./ for POSIX relative paths
        if self.is_posix and not target.startswith('/') and not target.startswith('./'):
             target = f"./{target}"
        self.run_command([target])

    def cleanup(self):
        for f in self.output_files:
            if f.exists():
                try:
                    f.unlink()
                except OSError:
                    pass

def main():
    parser = argparse.ArgumentParser(description="Professional Auto Compiler & Runner")
    parser.add_argument("files", nargs="*", help="Files to compile and run")
    parser.add_argument("-m", "--multi", action="store_true", help="Compile multi-files")
    parser.add_argument("-f", "--flags", type=str, default="", help='Compiler flags')
    
    # Process -f-flags without space
    processed_args = []
    i = 1
    while i < len(sys.argv):
        arg = sys.argv[i]
        if arg.startswith("-f") and len(arg) > 2:
            processed_args.append("-f")
            processed_args.append(arg[2:])
        else:
            processed_args.append(arg)
        i += 1

    args = parser.parse_args(processed_args)
    runner = CompilerRunner(flags=args.flags)

    # 1. Check if files provided
    if args.files:
        try:
            runner.compile_and_run(args.files, args.multi)
        finally:
            runner.cleanup()
        return 0

    # 2. No files provided -> Check for implicit Cargo Project
    if Path("Cargo.toml").exists():
        # Auto-detect cargo project
        runner.run_cargo_mode(Path("Cargo.toml"))
        return 0

    # 3. No files, No Cargo -> Fallback to Input
    try:
        val = input("No file given, enter file names: ").strip()
        if val: 
            args.files = shlex.split(val)
            runner.compile_and_run(args.files, args.multi)
    except (EOFError, KeyboardInterrupt):
        return 1
    finally:
        runner.cleanup()
        
    return 0

if __name__ == "__main__":
    sys.exit(main())