# Fast DDS QML Example with Conan 2 (using conanfile.py)

This project demonstrates how to use Fast DDS with a QML GUI, managed by Conan 2 using a conanfile.py recipe.

## Prerequisites
- FastDDSGen V2 tool from eProsima (included in FastDDS installation for Windows)
- CMake 3.15+
- MSVC C++ compiler supporting C++20
- Conan 2.0+
- Python 3.6+ (for Conan)
- Ninja build

## Building on Windows

1. **Setup and Build from Commandline**
Start `a x64 Native Tools Command Prompt for VS 2022`
```bash
PS> conan profile detect
PS> conan install .  --build=missing

# With VSCode
PS> code .

## From Commandline
PS> cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=build/generators/conan_toolchain.cmake
PS> cmake --build build
```
## License
This project is licensed under the BSD 3-Clause License. See the [LICENSE](./LICENSE) file for details.
