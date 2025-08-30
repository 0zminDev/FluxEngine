#pragma once

#include "ILogFormatter.h"
#include <unordered_map>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <cstring>
namespace Flux::Core::Formatters {
    
    class ConsoleFormatter : public ILogFormatter {
    private:
        // ANSI color codes for different log levels
        static const std::unordered_map<Flux::Core::Types::Level, const char*> levelColors;
        static const std::unordered_map<Flux::Core::Types::Level, const char*> levelNames;
        
        // Console formatting constants
        static constexpr const char* RESET_COLOR = "\033[0m";
        static constexpr const char* BOLD = "\033[1m";
        static constexpr const char* TIMESTAMP_COLOR = "\033[90m"; // Gray
        
        bool useColors;
        bool showTimestamp;
        bool showContext;
        
    public:
        explicit ConsoleFormatter(bool colors = true, bool timestamp = true, bool context = true)
            : useColors(colors), showTimestamp(timestamp), showContext(context) {}
        
        std::string format(const LogEntry& entry) const override;
        const char* getLevelString(Flux::Core::Types::Level level) const override;
        
        void setUseColors(bool enabled) { useColors = enabled; }
        void setShowTimestamp(bool enabled) { showTimestamp = enabled; }
        void setShowContext(bool enabled) { showContext = enabled; }
        
    private:
        const char* getLevelColor(Flux::Core::Types::Level level) const;
        std::string getCurrentTimestamp() const;
    };
    
}
