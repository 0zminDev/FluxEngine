#pragma once

#include "loggerExtensions.h"
#include <string>

namespace Flux::Core {
    class ScopedLoggerContext {
    private:
        LoggerExtensions* logger;
        std::string originalContext;
        
    public:
        explicit ScopedLoggerContext(LoggerExtensions* loggerInstance, const std::string& newContext)
            : logger(loggerInstance) {
            if (logger) {
                originalContext = logger->getSystemContext();
                logger->setSystemContext(newContext);
            }
        }
        
        ~ScopedLoggerContext() {
            if (logger) {
                logger->setSystemContext(originalContext);
            }
        }
        
        ScopedLoggerContext(const ScopedLoggerContext&) = delete;
        ScopedLoggerContext& operator=(const ScopedLoggerContext&) = delete;
        
        ScopedLoggerContext(ScopedLoggerContext&& other) noexcept
            : logger(other.logger), originalContext(std::move(other.originalContext)) {
            other.logger = nullptr;
        }
        
        ScopedLoggerContext& operator=(ScopedLoggerContext&& other) noexcept {
            if (this != &other) {
                if (logger) {
                    logger->setSystemContext(originalContext);
                }
                
                logger = other.logger;
                originalContext = std::move(other.originalContext);
                other.logger = nullptr;
            }
            return *this;
        }
        
        LoggerExtensions* operator->() { return logger; }
        LoggerExtensions* get() { return logger; }
        
        explicit operator bool() const { return logger != nullptr; }
    };
    
}
