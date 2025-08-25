# FluxEngine

[![CI/CD](https://github.com/0zminDev/FluxEngine/actions/workflows/ci-cd.yml/badge.svg)](https://github.com/0zminDev/FluxEngine/actions/workflows/ci-cd.yml)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)](docs/CI-CD.md)
[![Vulkan](https://img.shields.io/badge/Vulkan-1.3.290.0-red.svg)](https://vulkan.lunarg.com/)

Cross-platform game engine project built with C++23 and Vulkan. Supports Windows, Linux, and macOS with comprehensive CI/CD pipeline.

## Quick Start

```bash
# Clone the repository
git clone --recursive https://github.com/0zminDev/FluxEngine.git
cd FluxEngine

# Test your environment (optional)
./scripts/local-ci-test.sh  # Linux/macOS
# or
.\scripts\local-ci-test.ps1  # Windows

# Build and run
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
./build/bin/windows/Sandbox  # Linux/macOS
# or
.\build\bin\windows\Sandbox.exe  # Windows
```

For detailed setup instructions, see the platform-specific sections below.

## Requirements

- Windows 10/11, Linux (Ubuntu/Debian), macOS
- C++23 compiler (clang)
- cmake >= 3.25
- ninja
- Vulkan SDK

## Windows (MSYS2 + MinGW64)

1. Install MSYS2

2. Open MSYS2 MinGW64 and run:

    ```batch
    pacman -Syu
    pacman -S --needed mingw-w64-x86_64-clang mingw-w64-x86_64-cmake mingw-w64-x86_64-ninja
    ```

3. Ensure /mingw64/bin is in PATH:

    ```batch
    which clang
    which cmake
    which ninja
    ```

## Linux / macOS

1. Install dependencies:

   ### Ubuntu/Debian

    ```batch
    sudo apt update
    sudo apt install -y clang cmake ninja-build libvulkan-dev
    ```

   ### macOS (using Homebrew)

    ```batch
    brew install llvm cmake ninja
    export PATH="/usr/local/opt/llvm/bin:$PATH"  # or /opt/homebrew/opt/llvm/bin for Apple Silicon
    ```

2. Make it executable:

    ```batch
    chmod +x FluxBuild.sh
    ```

## Build Instructions

### Windows

```batch
./FluxBuild.ps1 build
./FluxBuild.ps1 build -Config Debug
./FluxBuild.ps1 run
./FluxBuild.ps1 rebuild
./FluxBuild.ps1 test
./FluxBuild.ps1 clean
```

### Linux/macOS

```batch
./FluxBuild.sh build
./FluxBuild.sh build Debug
./FluxBuild.sh run
./FluxBuild.sh test
./FluxBuild.sh rebuild
```

## Directory Structure

```batch
/engine/src           - Engine source files
/sandbox/src          - Sandbox executable source
/studio/src           - Studio executable source
/games/testGame/src   - Example game source
/tests                - Unit tests for engine and games
/extern/Catch2        - Catch2 submodule
/.github/workflows    - CI/CD
/build                - Build directory (auto-created)
```

- All binaries and shared libraries will be placed in build/bin/**platform**
- Windows uses MSYS2 paths automatically
- Linux/macOS scripts use native paths
- Highly encouraging to add RootDir to PATH so you cann use FluxBuild directly
