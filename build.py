import os
import subprocess

def run_meson_compile(relative_build_dir):
    script_dir = os.path.dirname(os.path.abspath(__file__))
    build_dir = os.path.join(script_dir, relative_build_dir)

    build_ninja_path = os.path.join(build_dir, 'build.ninja')
    if not os.path.exists(build_ninja_path):
        print("Setting up the Meson build directory...")
        setup_result = subprocess.run(['meson', 'setup', build_dir], capture_output=True, text=True)
        print("Setup Output:\n", setup_result.stdout)
        if setup_result.returncode != 0:
            print("Setup Errors:\n", setup_result.stderr)
            print("Setup failed, attempting to compile anyway...")
    
    os.chdir(build_dir)
    
    print("Compiling...")
    compile_result = subprocess.run(['meson', 'compile'], capture_output=True, text=True)
    
    print("Compile Output:\n", compile_result.stdout)
    print("Compile Errors:\n", compile_result.stderr)

    if compile_result.returncode == 0:
        print("Meson compile was successful.")
    else:
        print("Meson compile failed.")

build_directory = './build'
run_meson_compile(build_directory)