#include "PlainTextFormatter.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <cstring>

namespace Flux::Core::Formatters {
    
    std::string PlainTextFormatter::format(const LogEntry& entry) const {
        std::ostringstream formatted;
        
        if (showTimestamp) {
            auto now = std::chrono::system_clock::now();
            auto time_t = std::chrono::system_clock::to_time_t(now);
            formatted << "[" << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S") << "] ";
        }
        
        formatted << "[" << getLevelString(entry.level) << "] ";
        
        if (showContext && entry.systemContext && strlen(entry.systemContext) > 0) {
            formatted << "[" << entry.systemContext << "] ";
        }
        
        formatted << entry.message << "\n";
        
        return formatted.str();
    }
    
    const char* PlainTextFormatter::getLevelString(Flux::Core::Types::Level level) const {
        switch (level) {
            case Flux::Core::Types::Level::LOG_TRACE: return "TRACE";
            case Flux::Core::Types::Level::LOG_DEBUG: return "DEBUG";
            case Flux::Core::Types::Level::LOG_INFO:  return "INFO";
            case Flux::Core::Types::Level::LOG_WARN:  return "WARN";
            case Flux::Core::Types::Level::LOG_ERROR: return "ERROR";
            case Flux::Core::Types::Level::LOG_FATAL: return "FATAL";
            default: return "UNKNOWN";
        }
    }
    
}
