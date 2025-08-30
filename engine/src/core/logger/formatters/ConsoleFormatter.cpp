#include "ConsoleFormatter.h"

namespace Flux::Core::Formatters {    
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
