#pragma once

#include "core/logger/types/loggerLevel.h"
#include <string>

namespace Flux::Core::Formatters {
    
    struct LogEntry {
        Flux::Core::Types::Level level;
        const char* message;
        const char* timestamp;
        const char* systemContext; // System context (like "Engine", "Sandbox", "Physics")
    };
    
    class ILogFormatter {
    public:
        virtual ~ILogFormatter() = default;
        virtual std::string format(const LogEntry& entry) const = 0;
        virtual const char* getLevelString(Flux::Core::Types::Level level) const = 0;
    };
    
}
