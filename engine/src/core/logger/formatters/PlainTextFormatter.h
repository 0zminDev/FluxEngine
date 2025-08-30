#pragma once

#include "ILogFormatter.h"

namespace Flux::Core::Formatters {
    
    class PlainTextFormatter : public ILogFormatter {
    private:
        bool showTimestamp;
        bool showContext;
        
    public:
        explicit PlainTextFormatter(bool timestamp = true, bool context = true)
            : showTimestamp(timestamp), showContext(context) {}
        
        std::string format(const LogEntry& entry) const override;
        const char* getLevelString(Flux::Core::Types::Level level) const override;
        
        void setShowTimestamp(bool enabled) { showTimestamp = enabled; }
        void setShowContext(bool enabled) { showContext = enabled; }
    };
    
}
