#pragma once

#include "defines.h"

#include "logger.h"

namespace Flux::Core {
	class LoggerExtensions {
			ILogger* impl = nullptr;
			std::string systemContext;
		public:
			LoggerExtensions() = default;
			LoggerExtensions(ILogger* loggerImpl) : impl(loggerImpl) {}
			LoggerExtensions(ILogger* loggerImpl, const std::string& context) 
				: impl(loggerImpl), systemContext(context) {}

			// System context management
			void setSystemContext(const std::string& context) { systemContext = context; }
			const std::string& getSystemContext() const { return systemContext; }

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
