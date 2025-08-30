#pragma once

#include "defines.h"

#include "logger.h"

namespace Flux::Core {
	class LoggerExtensions {
			ILogger* impl = nullptr;
			std::string systemContext;
			
			LoggerExtensions* baseLogger = nullptr;
			std::string originalContext;
			
		public:
			LoggerExtensions() = default;
			LoggerExtensions(ILogger* loggerImpl) : impl(loggerImpl) {}
			LoggerExtensions(ILogger* loggerImpl, const std::string& context) 
				: impl(loggerImpl), systemContext(context) {}
			
			LoggerExtensions(LoggerExtensions* base, const std::string& newContext)
				: impl(base->impl), baseLogger(base) {
				originalContext = base->getSystemContext();
				systemContext = newContext;
				base->setSystemContext(newContext);
			}
			
			~LoggerExtensions() {
				if (baseLogger) {
					baseLogger->setSystemContext(originalContext);
				}
			}
			
			LoggerExtensions(const LoggerExtensions&) = delete;
			LoggerExtensions& operator=(const LoggerExtensions&) = delete;
			
			LoggerExtensions(LoggerExtensions&& other) noexcept
				: impl(other.impl), systemContext(std::move(other.systemContext)),
				  baseLogger(other.baseLogger), originalContext(std::move(other.originalContext)) {
				other.baseLogger = nullptr;
			}

			void setSystemContext(const std::string& context) { systemContext = context; }
			const std::string& getSystemContext() const { return systemContext; }
			
			LoggerExtensions withContext(const std::string& context) {
				return LoggerExtensions(this, context);
			}

			// TODO: Implement custom string
			EXPORT void Trace(const char* msg);
			EXPORT void Debug(const char* msg);
			EXPORT void Info(const char* msg);
			EXPORT void Warn(const char* msg);
			EXPORT void Error(const char* msg);
			EXPORT void Fatal(const char* msg);
			
		private:
			void logWithContext(Types::Level level, const char* msg);
	};
}
