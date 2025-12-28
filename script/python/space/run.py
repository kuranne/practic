#!/usr/bin/env python3
# Author: Kuranne Maisa
# Language: Python
# Version of Language: 3.14.2t

import os
import subprocess as spc
import argparse

# Compile c & c++
def compile_action(cmd):
    if spc.run(cmd).returncode != 0:
        return False
    return True

# Select Compiler for c/c++
def compiler(extension):
    return "gcc" if extension == ".c" else "g++"

# I do this for when I use in Windows... , no maybe not. Should I delete this?
def name_out(name):
    f"./{name}.out" if os.name == "posix" else f".\{name}.out"

# Complie multi files of c or c++ file
# Seem like gcc || g++ name name2 -I header -o name.out
def multi_file_compile(args):
    
    # Split between source files and header files
    cfiles = [f for f in args.files if f.endswith(('.c', 'cpp', '.cc'))]
    hfiles = [f for f in args.files if f.endswith(('hpp', '.h'))]
    if not cfiles:
        print("File not provided")
        return None
    
    # Spilt first filename into name and extension for out_name
    name, extension = os.path.splitext(cfiles[0])

    out_name = name_out(name)    
    prog = compiler(extension)
    
    cmd = [prog] + cfiles + [f"-I{f}" for f in hfiles] + ["-o", out_name]

    if not compile_action(cmd):
        print("Failed to compile")
        return None
    
    return out_name

def main():
    # Just for exit code
    error_code = 0

    # Argparse Initialize
    parser = argparse.ArgumentParser(description="Auto Compile & run")
    # Argruments
    parser.add_argument("files", nargs="*", help="Files name need to compile and run")
    # Option
    parser.add_argument("-m", "--multi", action="store_true", help="flag to tell compile multi files into a binary")
    args = parser.parse_args()
    
    out_name = None

    # When there is no given filename, This will finally recieve some word
    # Maybe I will delete this after because it just a bit bother
    while not args.files:
        print("No file given, enter file name: ")
        recieve = None
        try:
            recieve = input()
        except EOFError:
            print("Failed to recieve input")
            error_code += 1
            break
        try:
            if recieve.split()[0] not in ['\n', '\0', None, '', ' ']:
                args.files.append(recieve)
        except IndexError:
            continue

    # Main Run Function
    else:
        if args.multi:
            out_name = multi_file_compile(args)
            if out_name:
               spc.run([out_name])
            else:
               error_code += 1

        else:
            # This will loop until no file to run
            for filename in args.files:

                name, extension = os.path.splitext(filename)
                # Prog Store a Compiler or Inteprenter for Programming Language
                prog = ""
                
                match extension:
                    # Will check language want to compile first before run
                    # Then If language don't need to compile or it have a compile & run built-in
                    # That will be run that tool
                    
                    # The C file
                    case ".c":
                        out_name = f"./{name}.out" if os.name == "posix" else f".\\{name}.out"
                        cmd = ["gcc", filename, "-o", out_name]

                    # The CPP file
                    case ".cpp":
                        out_name = f"./{name}.out" if os.name == "posix" else f".\\{name}.out"
                        cmd = ["g++", filename, "-o", out_name]

                    case _:
                        # non-compile or compile and run built-in language
                        match extension:
                            # JAVA file
                            case ".java":
                                prog = "java"
                            # Python file
                            case ".py":
                                prog = "python3" if os.name == "posix" else "python"
                            case _:
                                print("Unknow extension")
                                error_code += 1
                                continue
                        
                        # Run
                        if spc.run([prog, filename]).returncode != 0:
                            error_code += 1
                            continue
                # Run after compiled
                if compile_action(cmd):
                    spc.run([out_name])
                else:
                    error_code += 1
    
    # Clear compiled package file
    if out_name != None:
        spc.run(["rm", out_name])
    
    return error_code
                        
if __name__ == "__main__":
    status = int(main())
    exit(status)