#include "ConsoleFormatter.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <cstring>

namespace Flux::Core::Formatters {
    
    const std::unordered_map<Flux::Core::Types::Level, const char*> ConsoleFormatter::levelColors = {
        {Flux::Core::Types::Level::LOG_TRACE, "\033[37m"},    // White
        {Flux::Core::Types::Level::LOG_DEBUG, "\033[36m"},    // Cyan
        {Flux::Core::Types::Level::LOG_INFO, "\033[32m"},     // Green
        {Flux::Core::Types::Level::LOG_WARN, "\033[33m"},     // Yellow
        {Flux::Core::Types::Level::LOG_ERROR, "\033[31m"},    // Red
        {Flux::Core::Types::Level::LOG_FATAL, "\033[35m"}     // Magenta
    };
    
    const std::unordered_map<Flux::Core::Types::Level, const char*> ConsoleFormatter::levelNames = {
        {Flux::Core::Types::Level::LOG_TRACE, "TRACE"},
        {Flux::Core::Types::Level::LOG_DEBUG, "DEBUG"},
        {Flux::Core::Types::Level::LOG_INFO, "INFO "},
        {Flux::Core::Types::Level::LOG_WARN, "WARN "},
        {Flux::Core::Types::Level::LOG_ERROR, "ERROR"},
        {Flux::Core::Types::Level::LOG_FATAL, "FATAL"}
    };
    
    ConsoleFormatter::~ConsoleFormatter() {}
    
    std::string ConsoleFormatter::format(const LogEntry& entry) const {
        std::ostringstream formatted;
		
        if (showTimestamp) {
            if (useColors) {
                formatted << TIMESTAMP_COLOR;
            }
            formatted << "[" << getCurrentTimestamp() << "]";
            if (useColors) {
                formatted << RESET_COLOR;
            }
            formatted << " ";
        }
        
        if (useColors) {
            formatted << getLevelColor(entry.level) << BOLD;
        }
        formatted << "[" << getLevelString(entry.level) << "]";
        if (useColors) {
            formatted << RESET_COLOR;
        }
        formatted << " ";
        
        if (showContext && entry.systemContext && strlen(entry.systemContext) > 0) {
            if (useColors) {
                formatted << "\033[94m"; // Light blue
            }
            formatted << "[" << entry.systemContext << "]";
            if (useColors) {
                formatted << RESET_COLOR;
            }
            formatted << " ";
        }
        
        formatted << entry.message << "\n";
        
        return formatted.str();
    }
    
    const char* ConsoleFormatter::getLevelString(Flux::Core::Types::Level level) const {
        auto it = levelNames.find(level);
        return (it != levelNames.end()) ? it->second : "UNKNOWN";
    }
    
    const char* ConsoleFormatter::getLevelColor(Flux::Core::Types::Level level) const {
        if (!useColors) {
            return "";
        }
        
        auto it = levelColors.find(level);
        return (it != levelColors.end()) ? it->second : "\033[37m"; // Default to white
    }
    
    std::string ConsoleFormatter::getCurrentTimestamp() const {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;
        
        std::ostringstream timestamp;
        timestamp << std::put_time(std::localtime(&time_t), "%H:%M:%S");
        timestamp << "." << std::setfill('0') << std::setw(3) << ms.count();
        
        return timestamp.str();
    }
    
}
