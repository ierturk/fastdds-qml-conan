# Fast DDS QML Example with Conan 2 (using conanfile.py)

This project demonstrates how to use Fast DDS with a QML GUI, managed by Conan 2 using a conanfile.py recipe.

## Prerequisites

- CMake 3.15+
- C++ compiler supporting C++20
- Conan 2.0+
- Python 3.6+ (for Conan)

## Building on Windows

1. **Setup Conan Profile**
```bash
conan profile detect
conan install .  --build=missing
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake
cmake --build build
```
## License
This project is licensed under the BSD 3-Clause License. See the [LICENSE](./LICENSE) file for details.
