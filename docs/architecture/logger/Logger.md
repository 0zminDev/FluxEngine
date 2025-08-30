# FluxEngine Logger System Architecture

## Overview

The FluxEngine Logger System implements a sophisticated, multi-layered logging infrastructure following the **inverse dependency inheritance** pattern. This design provides a highly flexible, performant, and maintainable logging solution that scales from simple console output to complex multi-scope, multi-context production logging.

## Architectural Foundation

### Inverse Dependency Inheritance Pattern

The Logger system exemplifies FluxEngine's core architectural principle where:

- **Core Layer (Layer 1)**: Defines abstract interfaces and contracts
- **Platform Layer (Layer 0)**: Provides concrete, platform-optimized implementations
- **Application Layer (Layer 2)**: Consumes logging services through clean abstractions

```text
┌─────────────────────────────────────────────────────────────┐
│ Application Layer                                           │
│ ┌─────────────────────────────────────────────────────────┐ │
│ │ LoggerExtensions::Trace/Debug/Info/Warn/Error/Fatal    │ │
│ │ • High-level convenience methods                        │ │
│ │ • Type-safe API for application code                   │ │
│ └─────────────────────────────────────────────────────────┘ │
├─────────────────────────────────────────────────────────────┤
│ Core Layer (engine/src/core/logger/)                       │
│ ┌───────────────┬───────────────┬─────────────────────────┐ │
│ │   ILogger     │ ILoggerScope  │    ILoggerContext       │ │
│ │ • log()       │ • log()       │ • getIdentifier()       │ │
│ │ • broadcast() │ • addContext()│ • isValid()             │ │
│ │ • useScope()  │ • setCurrent()│ • Platform-agnostic     │ │
│ └───────────────┴───────────────┴─────────────────────────┘ │
├─────────────────────────────────────────────────────────────┤
│ Platform Layer (engine/src/platform/{os}/logger/)          │
│ ┌───────────────┬───────────────┬─────────────────────────┐ │
│ │Platform Logger│Platform Scope │  Platform Context      │ │
│ │• Windows API  │• Console/File │ • HANDLE/FILE*/fd       │ │
│ │• Unix syslog  │• UI/API       │ • Platform handles      │ │
│ │• OS-optimized │• Scope mgmt   │ • Resource management   │ │
│ └───────────────┴───────────────┴─────────────────────────┘ │
└─────────────────────────────────────────────────────────────┘
```

## Core Components

### 1. ILogger Interface (Core Layer)

The foundational interface that defines the logging contract:

```cpp
namespace Flux::Core {
    class ILogger {
        std::vector<ILoggerScope*> scopes;
        ILoggerScope* currentScope = nullptr;
    public:
        virtual ~ILogger() = default;
        
        // Primary logging methods
        virtual void log(Types::Level level, const char* message) = 0;
        virtual void broadcast(Types::Level level, const char* message) = 0;
        
        // Scope management
        virtual const ILoggerScope* useScope(Types::Scope scope) const = 0;
        virtual const bool addScope(Types::Scope scope) const = 0;
        virtual const ILoggerScope* getCurrentScope() const = 0;
    };
}
```

**Responsibilities:**

- Define logging contract for platform implementations
- Manage collection of available scopes
- Coordinate scope switching and lifecycle
- Provide both targeted and broadcast logging capabilities

### 2. LoggerExtensions (Application Interface)

High-level convenience wrapper providing type-safe logging methods:

```cpp
namespace Flux::Core {
    class LoggerExtensions {
        ILogger* impl = nullptr;
    public:
        LoggerExtensions(ILogger* loggerImpl) : impl(loggerImpl) {}
        
        EXPORT void Trace(const char* msg);   // Types::Level::LOG_TRACE
        EXPORT void Debug(const char* msg);   // Types::Level::LOG_DEBUG
        EXPORT void Info(const char* msg);    // Types::Level::LOG_INFO
        EXPORT void Warn(const char* msg);    // Types::Level::LOG_WARN
        EXPORT void Error(const char* msg);   // Types::Level::LOG_ERROR
        EXPORT void Fatal(const char* msg);   // Types::Level::LOG_FATAL
    };
}
```

**Design Benefits:**

- **Type Safety**: Compile-time level verification
- **Convenience**: Eliminates need to specify level explicitly
- **Abstraction**: Hides platform complexity from application code
- **Performance**: Direct delegation to platform implementation

### 3. Scope System Architecture

#### ILoggerScope Interface

Scopes represent different logging environments with distinct behaviors:

```cpp
namespace Flux::Core {
    class ILoggerScope {
        std::vector<ILoggerContext*> contexts;
        ILoggerContext* currentContext = nullptr;
    public:
        virtual ~ILoggerScope() = default;
        virtual void log(Types::Level level, const char* message) = 0;
        virtual bool addContext(const std::string& identifier) = 0;
        virtual bool setCurrentContext(const std::string& identifier) = 0;
    };
}
```

#### Scope Types

```cpp
namespace Flux::Core::Types {
    enum Scope {
        CONSOLE,    // Terminal/console output
        FILE,       // File system logging
        UI,         // In-engine UI logging panels
        API,        // External API/service logging
        Broadcast   // Multi-scope simultaneous logging
    };
}
```

**Scope Responsibilities:**

- **Context Management**: Handle multiple contexts within scope
- **Output Routing**: Direct logs to appropriate destinations
- **Format Control**: Apply scope-specific formatting
- **Platform Adaptation**: Leverage platform-optimized APIs

### 4. Context System Architecture

#### ILoggerContext Interface

Contexts represent specific handles/resources within a scope:

```cpp
namespace Flux::Core {
    class ILoggerContext {
    public:
        virtual ~ILoggerContext() = default;
        virtual bool isValid() const = 0;
        virtual std::string getIdentifier() const = 0;
    };
}
```

**Context Examples by Scope:**

| Scope | Context Examples | Platform Handles |
|-------|------------------|------------------|
| CONSOLE | stdout, stderr | Windows: HANDLE, Unix: fd |
| FILE | log files, rotating logs | FILE*, file descriptors |
| UI | debug panels, HUD elements | UI widget references |
| API | network endpoints, services | socket handles, HTTP clients |

**Context Design Principles:**

- **Struct over Class**: Prefer data structures for explicit conventions
- **No Logic**: Contexts hold only data and identifiers
- **Resource Management**: Proper cleanup and validation
- **Platform Abstraction**: Hide platform-specific handle types

## Type System

### Logging Levels

```cpp
namespace Flux::Core::Types {
    enum class Level {
        LOG_TRACE,    // Detailed execution flow
        LOG_DEBUG,    // Development debugging information
        LOG_INFO,     // General informational messages
        LOG_WARN,     // Warning conditions
        LOG_ERROR,    // Error conditions requiring attention
        LOG_FATAL     // Critical errors causing termination
    };
}
```

### Color Support

```cpp
namespace Flux::Core::Types {
    enum class LoggerColor {
        DEFAULT,      // System default color
        RED,          // Errors, critical issues
        GREEN,        // Success, positive states
        BLUE,         // Informational content
        YELLOW,       // Warnings, caution
        CYAN,         // Debug information
        MAGENTA       // Special highlighting
    };
}
```

## Platform Implementation Strategy

### Layer 0: Platform-Specific Implementations

Each platform provides optimized implementations:

#### Windows Implementation

```cpp
namespace Flux::Platform {
    class WindowsLogger : public Flux::Core::ILogger {
        // Windows Console API integration
        // OutputDebugString support
        // Event Log integration
        // ANSI escape sequence support (Windows 10+)
    };
    
    class WindowsConsoleScope : public Flux::Core::ILoggerScope {
        // Console handle management
        // Color attribute setting
        // Unicode support
    };
    
    struct WindowsConsoleContext {
        HANDLE handle;
        std::string identifier;
        WORD defaultAttributes;
    };
}
```

#### Unix/Linux Implementation

```cpp
namespace Flux::Platform {
    class UnixLogger : public Flux::Core::ILogger {
        // syslog integration
        // ANSI escape sequences
        // File descriptor management
    };
    
    class UnixConsoleScope : public Flux::Core::ILoggerScope {
        // Terminal capability detection
        // ANSI color support
        // Signal handling
    };
    
    struct UnixConsoleContext {
        int fd;
        std::string identifier;
        bool colorSupported;
    };
}
```

## Orchestration and State Management

### Logger Orchestration

The main `ILogger` implementation orchestrates:

1. **Scope Management**: Adding, removing, and switching between scopes
2. **Message Routing**: Directing logs to appropriate scopes
3. **Broadcasting**: Simultaneous logging to multiple scopes
4. **Resource Lifecycle**: Proper initialization and cleanup

### Scope Orchestration

Each `ILoggerScope` implementation manages:

1. **Context Collection**: Multiple contexts within the scope
2. **Active Context**: Current target for log messages
3. **Context Switching**: Dynamic context selection
4. **Batching Logic**: Performance optimization through batching
5. **State Persistence**: Maintaining scope-specific settings

### Context State Management

Contexts provide:

1. **Handle Abstraction**: Platform-specific resource management
2. **Validation**: Ensure context resources are valid
3. **Identification**: Unique identifiers for context selection
4. **Metadata**: Additional context-specific information

## Advanced Features

### Batching and Performance

```cpp
class BatchingScope : public ILoggerScope {
    struct BatchEntry {
        Types::Level level;
        std::string message;
        std::chrono::timestamp time;
    };
    
    std::vector<BatchEntry> batch;
    size_t batchSize = 100;
    std::chrono::milliseconds flushInterval{100ms};
    
    void flushBatch();
    void scheduledFlush();
};
```

### Build Configuration Integration

```cpp
#ifdef FLUX_DEBUG_BUILD
    #define FLUX_LOG_LEVEL Types::Level::LOG_TRACE
#elif defined(FLUX_RELEASE_BUILD)
    #define FLUX_LOG_LEVEL Types::Level::LOG_WARN
#endif

// Compile-time level filtering
template<Types::Level MinLevel>
class LevelFilteredLogger : public ILogger {
    void log(Types::Level level, const char* message) override {
        if constexpr (level >= MinLevel) {
            impl->log(level, message);
        }
    }
};
```

### Thread Safety

```cpp
class ThreadSafeLogger : public ILogger {
    mutable std::shared_mutex scopeMutex;
    mutable std::mutex logMutex;
    
    void log(Types::Level level, const char* message) override {
        std::lock_guard<std::mutex> lock(logMutex);
        // Thread-safe logging implementation
    }
};
```

## Integration Patterns

### Engine Integration

```cpp
namespace Flux::Core {
    class Engine {
        std::unique_ptr<ILogger> logger;
        std::unique_ptr<LoggerExtensions> loggerExtensions;
        
    public:
        void initialize() {
            // Platform manager creates appropriate logger
            logger = platformManager->createLogger();
            loggerExtensions = std::make_unique<LoggerExtensions>(logger.get());
            
            // Setup default scopes
            logger->addScope(Types::Scope::CONSOLE);
            logger->addScope(Types::Scope::FILE);
            logger->useScope(Types::Scope::CONSOLE);
        }
        
        LoggerExtensions* getLogger() { return loggerExtensions.get(); }
    };
}
```

### Application Usage

```cpp
#include "FluxEngine.h"

int main() {
    Flux::Core::Engine engine;
    engine.initialize();
    
    auto* logger = engine.getLogger();
    
    // High-level convenience methods
    logger->Info("Application started");
    logger->Warn("Configuration file not found");
    logger->Error("Failed to load resource");
    
    // Scope switching for different outputs
    engine.getLogger()->useScope(Types::Scope::FILE);
    logger->Debug("Detailed debug information saved to file");
    
    return 0;
}
```

## Performance Considerations

### Design Goals

1. **Zero-Cost Abstraction**: Disabled levels compile to no-ops
2. **Minimal Allocation**: Avoid dynamic memory in hot paths
3. **Thread Safety**: Lock-free where possible, efficient locking otherwise
4. **Platform Optimization**: Leverage platform-specific optimizations

### Optimization Strategies

1. **Template Specialization**: Compile-time level filtering
2. **Memory Pools**: Pre-allocated message buffers
3. **Async Processing**: Background threads for I/O operations
4. **Batch Processing**: Reduce system call overhead
5. **Cache Optimization**: Minimize cache misses in logging paths

## Best Practices

### For Platform Implementers

1. **Follow Interface Contracts**: Implement all pure virtual methods
2. **Resource Management**: Proper RAII and cleanup
3. **Error Handling**: Graceful degradation on failures
4. **Platform Optimization**: Use platform-specific APIs for performance
5. **Thread Safety**: Consider concurrent access patterns

### For Application Developers

1. **Use LoggerExtensions**: Prefer high-level convenience methods
2. **Appropriate Levels**: Choose correct log levels for messages
3. **Performance Awareness**: Consider logging overhead in hot paths
4. **Scope Management**: Use appropriate scopes for different outputs
5. **Resource Cleanup**: Ensure proper logger lifecycle management

## Future Roadmap

### Phase 1: Foundation Completion

- [ ] Complete platform implementations (Windows, Linux, macOS)
- [ ] Basic scope implementations (Console, File)
- [ ] Color support integration
- [ ] Thread safety implementation

### Phase 2: Advanced Features

- [ ] Asynchronous logging with batching
- [ ] Rotating file logs with compression
- [ ] Network logging support
- [ ] Performance profiling integration

### Phase 3: Production Features

- [ ] Log aggregation and search
- [ ] Real-time monitoring integration
- [ ] Custom formatter plugins
- [ ] Log replay and debugging tools

The FluxEngine Logger System provides a robust foundation for sophisticated logging requirements while maintaining the simplicity and performance characteristics essential for game development.
