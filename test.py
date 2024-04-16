import os
import subprocess

def run_meson_test(relative_build_dir):
    script_dir = os.path.dirname(os.path.abspath(__file__))
    build_dir = os.path.join(script_dir, relative_build_dir)
    
    # Ensure the build directory exists and is likely configured
    if not os.path.exists(build_dir):
        print(f"Build directory does not exist: {build_dir}")
        return

    # Change to the build directory
    os.chdir(build_dir)

    # Run the meson test command
    print("Running Meson tests...")
    test_result = subprocess.run(['meson', 'test'], capture_output=True, text=True)
    
    # Output results from the test command
    print("Test Output:\n", test_result.stdout)
    print("Test Errors:\n", test_result.stderr)

    if test_result.returncode == 0:
        print("Meson tests ran successfully.")
    else:
        print("Meson tests failed.")

# Example usage:
build_directory = './build'  # Adjust this relative path as needed
run_meson_test(build_directory)