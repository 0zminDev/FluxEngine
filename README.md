# FluxEngine

Cross-platform game engine project. Supports Windows, Linux, and macOS.

Requirements:

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
./FluxBuild.ps1 clean
```

### Linux/macOS

```batch
./FluxBuild.sh build
./FluxBuild.sh build Debug
./FluxBuild.sh run
./FluxBuild.sh rebuild
```

## Directory Structure

```batch
/engine/src           - Engine source files
/sandbox/src          - Sandbox executable source
/studio/src           - Studio executable source
/games/testGame/src   - Example game source
/build                - Build directory (auto-created)
```

- All binaries and shared libraries will be placed in build/bin/**platform**
- Windows uses MSYS2 paths automatically
- Linux/macOS scripts use native paths
