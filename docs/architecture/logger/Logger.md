# FluxEngine Logger System Documentation

## Overview

The FluxEngine Logger System provides a comprehensive, cross-platform logging infrastructure designed for high-performance game development. Built following the inverse dependency inheritance pattern, it offers a clean interface abstraction with platform-specific implementations optimized for each target environment.

## Architecture

### Core Design Principles

- **Interface Abstraction**: Core logging interface (`ILogger`) defines contracts
- **Platform Optimization**: Platform-specific implementations maximize performance
- **Hierarchical Levels**: Six-tier logging levels for granular control
- **Color Support**: Rich console output with platform-native color handling
- **Scope-Based Processing**: Context-aware logging with scope management
- **Performance-First**: Designed for zero-overhead when disabled

### Layer Structure

```text
┌─────────────────────────────────────────────────────────────┐
│ Application Layer                                           │
│ ┌─────────────┬─────────────┬─────────────┬─────────────┐   │
│ │   Sandbox   │   Studio    │  TestGame   │    Tests    │   │
│ │ Logger::*() │ Logger::*() │ Logger::*() │ Logger::*() │   │
│ └─────────────┴─────────────┴─────────────┴─────────────┘   │
├─────────────────────────────────────────────────────────────┤
│ Core Layer (engine/src/core/logger/)                       │
│ ┌─────────────────────────────────────────────────────────┐ │
│ │ Logger Wrapper Class                                    │ │
│ │ • Trace() • Debug() • Info() • Warn() • Error() • Fatal│ │
│ │                                                         │ │
│ │ ILogger Interface                                       │ │
│ │ • log(Level, Color, message)                           │ │
│ │ • Level enum • Color enum                              │ │
│ └─────────────────────────────────────────────────────────┘ │
├─────────────────────────────────────────────────────────────┤
│ Platform Layer (engine/src/platform/{os}/logger/)          │
│ ┌─────────────┬─────────────┬─────────────┬─────────────┐   │
│ │WindowsLogger│ LinuxLogger │ macOSLogger │AndroidLogger│   │
│ │Console API  │ANSI Escapes │ANSI Escapes │Android Log  │   │
│ │OutputDebug  │   syslog    │   os_log    │    API      │   │
│ └─────────────┴─────────────┴─────────────┴─────────────┘   │
└─────────────────────────────────────────────────────────────┘
```

## Current Implementation Status

### ✅ Implemented Features

- **Core Interface**: `ILogger` abstraction with level and color support
- **Logging Levels**: Six-tier hierarchy (TRACE, DEBUG, INFO, WARN, ERROR, FATAL)
- **Color Enumeration**: Seven color options for enhanced readability
- **Wrapper Class**: Convenient `Logger` class with typed methods
- **Platform Support**: Windows, Linux, macOS implementations
- **Cross-Platform Build**: CMake integration with conditional compilation

### 🚧 Basic Implementation

- **Windows Logger**: Console output via `std::cout`
- **Color Support**: Enum defined but not platform-implemented
- **Level Filtering**: Interface ready but not implemented

### ❌ Planned Features

The following advanced features are designed but not yet implemented:

#### Performance & Optimization
- **Batch Processing**: Asynchronous log batching for high-throughput scenarios
- **Build-Type Flushing**: Debug vs Release mode optimization strategies
- **Zero-Cost Abstractions**: Compile-time level filtering

#### Advanced Features
- **Scope-Based Rich Text**: Context-aware formatting (console, file, UI)
- **Tag System**: Custom logger types with filterable tags
- **Time Management**: Timestamp formatting and timezone handling
- **Profiling Integration**: Performance metrics and timing data
- **Global/Local Level Control**: Runtime level filtering per scope
- **Search Support**: Log querying and filtering capabilities

## API Reference

### Core Interface

```cpp
namespace Flux::Core {
    // Logging levels in order of severity
    enum Level {
        LEVEL_TRACE,    // Detailed execution flow
        LEVEL_DEBUG,    // Development debugging
        LEVEL_INFO,     // General information
        LEVEL_WARN,     // Warning conditions
        LEVEL_ERROR,    // Error conditions
        LEVEL_FATAL     // Fatal errors
    };

    // Color options for enhanced readability
    enum Color {
        COLOR_DEFAULT,  // System default
        COLOR_RED,      // Errors, critical issues
        COLOR_GREEN,    // Success, positive states
        COLOR_BLUE,     // Information, neutral
        COLOR_YELLOW,   // Warnings, caution
        COLOR_CYAN,     // Debug information
        COLOR_MAGENTA   // Special highlighting
    };

    // Core logging interface
    class ILogger {
    public:
        virtual void log(Level level, Color color, const char* message) = 0;
        virtual ~ILogger() = default;
    };

    // Convenience wrapper class
    class Logger {
        ILogger* impl = nullptr;
    public:
        Logger(ILogger* loggerImpl) : impl(loggerImpl) {}
        
        void Trace(const char* msg);  // LEVEL_TRACE
        void Debug(const char* msg);  // LEVEL_DEBUG  
        void Info(const char* msg);   // LEVEL_INFO
        void Warn(const char* msg);   // LEVEL_WARN
        void Error(const char* msg);  // LEVEL_ERROR
        void Fatal(const char* msg);  // LEVEL_FATAL
    };
}
```

### Platform Implementations

#### Windows Logger
```cpp
namespace Flux::Platform {
    class WindowsLogger : public Flux::Core::ILogger {
    public:
        void log(Flux::Core::Level level, Flux::Core::Color color, 
                const char* message) override;
    };
}
```

**Current Implementation**: Basic console output via `std::cout`

**Planned Enhancements**:
- Windows Console API color support
- OutputDebugString integration
- Event Log integration for production

#### Linux Logger
```cpp
namespace Flux::Platform {
    class LinuxLogger : public Flux::Core::ILogger {
    public:
        void log(Flux::Core::Level level, Flux::Core::Color color, 
                const char* message) override;
    };
}
```

**Planned Features**:
- ANSI escape sequence color support
- syslog integration
- Journal (systemd) support

#### macOS Logger
```cpp
namespace Flux::Platform {
    class macOSLogger : public Flux::Core::ILogger {
    public:
        void log(Flux::Core::Level level, Flux::Core::Color color, 
                const char* message) override;
    };
}
```

**Planned Features**:
- ANSI escape sequence color support
- os_log integration
- Console.app compatibility

## Usage Examples

### Basic Logging
```cpp
#include "export.h"

int main() {
    // Platform manager initializes appropriate logger
    auto* platformLogger = PlatformManager::getLogger();
    Flux::Core::Logger logger(platformLogger);
    
    logger.Info("Application started");
    logger.Warn("Configuration file not found, using defaults");
    logger.Error("Failed to load texture: missing.png");
    logger.Fatal("Critical system failure");
    
    return 0;
}
```

### Custom Implementation
```cpp
class GameLogger : public Flux::Core::ILogger {
    void log(Flux::Core::Level level, Flux::Core::Color color, 
            const char* message) override {
        // Custom game-specific logging logic
        writeToGameLog(level, message);
        if (level >= LEVEL_ERROR) {
            notifyErrorHandler(message);
        }
    }
};
```

## Planned Feature Roadmap

### Phase 1: Color Implementation
- [ ] Windows Console API color support
- [ ] ANSI escape sequences for Unix platforms
- [ ] Terminal capability detection
- [ ] Fallback for non-color terminals

### Phase 2: Advanced Formatting
- [ ] Timestamp integration
- [ ] Caller information (file, line, function)
- [ ] Thread-safe logging
- [ ] Custom format strings

### Phase 3: Performance Optimization
- [ ] Asynchronous logging queue
- [ ] Batch processing with configurable buffer sizes
- [ ] Memory pool allocation for log messages
- [ ] Compile-time level filtering

### Phase 4: Scope & Context Management
- [ ] Hierarchical scopes (System, Subsystem, Component)
- [ ] Context-aware formatting (console vs file vs UI)
- [ ] Tag-based filtering system
- [ ] Runtime level configuration

### Phase 5: Advanced Features
- [ ] Log rotation and archival
- [ ] Network logging support
- [ ] Performance profiling integration
- [ ] Search and query capabilities
- [ ] Real-time log monitoring

## Performance Considerations

### Design Goals
- **Zero Overhead**: Disabled log levels should compile to no-ops
- **Minimal Allocation**: Avoid dynamic memory allocation in hot paths
- **Thread Safety**: Support concurrent logging from multiple threads
- **Low Latency**: Minimize impact on game loop performance

### Optimization Strategies
- **Compile-Time Filtering**: Use preprocessor macros for release builds
- **Async Processing**: Background thread for I/O operations
- **Memory Pooling**: Pre-allocated message buffers
- **Platform-Specific**: Leverage platform-optimized APIs

## Integration with FluxEngine

### Platform Manager Integration
The Logger system integrates with the Platform Manager for automatic initialization:

```cpp
// Platform Manager creates appropriate logger instance
ILogger* logger = PlatformManager::createLogger();

// Engine components receive logger through dependency injection
EngineSubsystem::initialize(logger);
```

### Build System Integration
CMake automatically includes platform-specific logger implementations:

```cmake
# Conditional compilation based on target platform
if(WIN32)
    target_sources(FluxEngine PRIVATE 
        engine/src/platform/windows/logger/logger.cpp)
elseif(UNIX AND NOT APPLE)
    target_sources(FluxEngine PRIVATE 
        engine/src/platform/linux/logger/logger.cpp)
elseif(APPLE)
    target_sources(FluxEngine PRIVATE 
        engine/src/platform/macos/logger/logger.cpp)
endif()
```

## Contributing

When extending the Logger system:

1. **Follow Interface Contracts**: Implement `ILogger` completely
2. **Platform Optimization**: Leverage platform-specific APIs
3. **Performance First**: Consider impact on game loop performance
4. **Test Coverage**: Include unit tests for new functionality
5. **Documentation**: Update this document with new features

The Logger system serves as a foundational component for FluxEngine's debugging, monitoring, and development workflow, designed to scale from simple console output to sophisticated production logging infrastructure.