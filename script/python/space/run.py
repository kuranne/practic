#!/usr/bin/env python3
import os
import subprocess as spc
import argparse
import sys
from pathlib import Path
from typing import List

class CompilerRunner:
    def __init__(self):
        self.is_posix = os.name == "posix"
        self.output_files: List[Path] = []

    def get_executable_path(self, source_path: Path) -> Path:
        # Create PATH for OS
        name = source_path.stem
        return Path(f"./{name}.out" if self.is_posix else f"{name}.exe")

    def run_command(self, cmd: List[str]) -> bool:
        # Execute command & error
        try:
            result = spc.run(cmd, check=False)
            return result.returncode == 0
        except FileNotFoundError:
            print(f"Error: Command '{cmd[0]}' not found.")
            return False

    def compile_and_run(self, files: List[str], multi: bool = False):
        if not files:
            return

        file_paths = [Path(f) for f in files]
        
        if multi:
            self._handle_multi_compile(file_paths)
        else:
            for fp in file_paths:
                self._handle_single_file(fp)

    def _handle_multi_compile(self, paths: List[Path]):
        sources = [p for p in paths if p.suffix in ('.c', '.cpp', '.cc')]
        headers = [p for p in paths if p.suffix in ('.h', '.hpp')]
        
        if not sources:
            return

        main_source = sources[0]
        compiler = "gcc" if main_source.suffix == ".c" else "g++"
        out_name = self.get_executable_path(main_source)
        
        # Build command: compiler sources -Iheaders -o output
        cmd = [compiler] + [str(s) for s in sources]
        for h in headers:
            cmd.append(f"-I{h.parent}")
        cmd += ["-o", str(out_name)]

        if self.run_command(cmd):
            self.output_files.append(out_name)
            self.run_command([f"./{out_name}" if self.is_posix else str(out_name)])

    def _handle_single_file(self, fp: Path):
        ext = fp.suffix
        out_name = self.get_executable_path(fp)
        match ext:
            case ".py":
                prog = "python3" if self.is_posix else "python"
                self.run_command([prog, str(fp)])
            case ".java":
                self.run_command(["java", str(fp)])
            case _:
                # Compile before run languages
                if ext in ('.c', '.cpp'):
                    compiler = "gcc" if ext == ".c" else "g++"
                    if self.run_command([compiler, str(fp), "-o", str(out_name)]):
                        self.output_files.append(out_name)
                        self.run_command([f"./{out_name}" if self.is_posix else str(out_name)])
                else:
                    print(f"Unsupported extension: {ext}")

    def cleanup(self):
        # This will Remove executable file after ran
        for f in self.output_files:
            if f.exists():
                f.unlink()

def main():
    parser = argparse.ArgumentParser(description="Professional Auto Compiler & Runner")
    parser.add_argument("files", nargs="*", help="Files to compile and run")
    parser.add_argument("-m", "--multi", action="store_true", help="Compile multiple files into one binary")
    args = parser.parse_args()

    # Interactive input if no files provided
    if not args.files:
        try:
            val = input("No file given, enter file names: ").strip()
            if val: args.files = val.split()
        except EOFError:
            return 1

    runner = CompilerRunner()
    try:
        runner.compile_and_run(args.files, args.multi)
    finally:
        runner.cleanup()
    return 0

if __name__ == "__main__":
    sys.exit(main())