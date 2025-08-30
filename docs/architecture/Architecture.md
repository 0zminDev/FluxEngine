# FluxEngine Architecture Documentation

## Overview

FluxEngine employs a **layered modular architecture** with **inverse dependency inheritance** as its core design principle. This architectural pattern ensures clean separation of concerns, platform independence, and maintainable code organization.

## Architectural Principles

### 1. Inverse Dependency Inheritance

The engine follows the Dependency Inversion Principle where:

- High-level modules (Core layer) define interfaces
- Low-level modules (Platform layer) implement these interfaces
- Dependencies flow from concrete implementations toward abstractions

### 2. Layered Modular Design

The architecture can be visualized as a 2D matrix where:

- **Rows** represent architectural layers (vertical separation)
- **Columns** represent functional modules (horizontal separation)
- **Modules** can span multiple layers when needed

## Layer Structure

```text
┌─────────────────────────────────────────────────────────────┐
│ Layer 2: Application Layer                                  │
│ ┌─────────┬─────────┬─────────┬─────────┬─────────┬────────┐ │
│ │ Sandbox │ Studio  │TestGame │ Engine  │  Tests  │   ...  │ │
│ └─────────┴─────────┴─────────┴─────────┴─────────┴────────┘ │
├─────────────────────────────────────────────────────────────┤
│ Layer 1: Core Layer (engine/src/core/)                     │
│ ┌─────────┬─────────┬─────────┬─────────┬─────────┬────────┐ │
│ │ Logger  │ Engine  │ Memory  │ Events  │ ECS     │   ...  │ │
│ │ (IFace) │ Manager │ Manager │ System  │ System  │        │ │
│ └─────────┴─────────┴─────────┴─────────┴─────────┴────────┘ │
├─────────────────────────────────────────────────────────────┤
│ Layer 0: Platform Layer (engine/src/platform/)             │
│ ┌─────────┬─────────┬─────────┬─────────┬─────────┬────────┐ │
│ │ Logger  │ Window  │ Input   │ Audio   │ Graphics│   ...  │ │
│ │ (Impl)  │ System  │ System  │ System  │ System  │        │ │
│ └─────────┴─────────┴─────────┴─────────┴─────────┴────────┘ │
└─────────────────────────────────────────────────────────────┘
```

## Module Implementation Pattern

### Cross-Layer Module Example: Logger System

The Logger module demonstrates how a single functional module spans multiple architectural layers:

#### Layer 1 (Core): Interface Definition

```cpp
// engine/src/core/logger/logger.h
namespace Flux::Core {
    enum Level { TRACE, DEBUG, INFO, WARN, ERROR, FATAL };
    enum Color { DEFAULT, RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA };
    
    class ILogger {
    public:
        virtual void log(Level level, Color color, const char* message) = 0;
        virtual ~ILogger() = default;
    };
    
    class Logger {
        ILogger* impl = nullptr;
    public:
        Logger(ILogger* loggerImpl) : impl(loggerImpl) {}
        void Trace(const char* msg);
        void Debug(const char* msg);
        // ... other methods
    };
}
```

#### Layer 0 (Platform): Concrete Implementations

```cpp
// engine/src/platform/windows/logger/logger.h
namespace Flux::Platform {
    class WindowsLogger : public Flux::Core::ILogger {
    public:
        void log(Flux::Core::Level level, Flux::Core::Color color, 
                const char* message) override;
    };
}
```

## Directory Structure Mapping

```text
FluxEngine/
├── engine/src/
│   ├── core/                    # Layer 1: Core abstractions
│   │   ├── logger/             # Logger module (interface)
│   │   ├── engine.h            # Engine module (interface)
│   │   └── ...
│   ├── platform/               # Layer 0: Platform implementations
│   │   ├── windows/logger/     # Logger module (Windows impl)
│   │   ├── linux/logger/       # Logger module (Linux impl)
│   │   ├── macos/logger/       # Logger module (macOS impl)
│   │   └── platformManager.h   # Platform abstraction coordinator
│   ├── defines.h               # Global definitions
│   ├── types.h                 # Core type definitions
│   └── export.h                # Unified API export
├── sandbox/                    # Layer 2: Test application
├── studio/                     # Layer 2: Engine editor
├── games/testGame/             # Layer 2: Sample game
└── tests/                      # Layer 2: Unit tests
```

## Dependency Management

### Include Hierarchy

The engine uses a carefully orchestrated include system to prevent circular dependencies:

1. **Foundation Layer**: `defines.h`, `types.h`
2. **Core Interfaces**: `core/logger/logger.h`, `core/engine.h`
3. **Platform Implementations**: Platform-specific headers (conditional)
4. **Platform Manager**: `platform/platformManager.h`
5. **Unified Export**: `export.h` (single entry point)

### Circular Dependency Prevention

- Headers included by `export.h` only include `defines.h`
- Forward declarations used extensively in header files
- Implementation files (`.cpp`) include `export.h` for full type access
- `#pragma once` combined with careful include ordering

## Build System Integration

### CMake Configuration

```cmake
# Shared library with all engine sources
add_library(FluxEngine SHARED ${ENGINE_SOURCES})

# Platform-specific configurations
if(WIN32)
    set_target_properties(FluxEngine PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# Applications link against the engine
add_executable(Sandbox sandbox/src/main.cpp)
target_link_libraries(Sandbox PRIVATE FluxEngine)
```

## Platform Abstraction Strategy

### Conditional Compilation

```cpp
// export.h - Platform-specific includes
#if CURRENT_PLATFORM == PLATFORM_WINDOWS
    #include "platform/windows/logger/logger.h"
#elif CURRENT_PLATFORM == PLATFORM_LINUX
    #include "platform/linux/logger/logger.h"
#elif CURRENT_PLATFORM == PLATFORM_MACOS
    #include "platform/macos/logger/logger.h"
#endif
```

### Runtime Platform Management

The `PlatformManager` class coordinates platform-specific implementations:

- Initializes appropriate platform loggers
- Manages platform-specific resources
- Provides unified interface for cross-platform operations

## Benefits of This Architecture

1. **Modularity**: Each functional area is cleanly separated
2. **Platform Independence**: Core logic is completely platform-agnostic
3. **Extensibility**: New modules follow the same layered pattern
4. **Testability**: Interfaces enable easy mocking and unit testing
5. **Maintainability**: Clear separation of concerns and dependencies
6. **Scalability**: Architecture supports growth without structural changes

## Future Expansion

New modules should follow this pattern:

1. Define core interface in `engine/src/core/{module}/`
2. Implement platform-specific versions in `engine/src/platform/{platform}/{module}/`
3. Register with `PlatformManager` for runtime coordination
4. Add to `export.h` include hierarchy
5. Ensure proper dependency ordering

This architecture provides a solid foundation for building a cross-platform game engine while maintaining clean, maintainable, and extensible code.
