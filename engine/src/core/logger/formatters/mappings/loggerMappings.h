
#include <unordered_map>
#include "core/logger/types/loggerLevel.h"
#include "ConsoleFormatter.h"

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
        {Flux::Core::Types::Level::LOG_INFO, "INFO"},
        {Flux::Core::Types::Level::LOG_WARN, "WARN"},
        {Flux::Core::Types::Level::LOG_ERROR, "ERROR"},
        {Flux::Core::Types::Level::LOG_FATAL, "FATAL"}
    };
}