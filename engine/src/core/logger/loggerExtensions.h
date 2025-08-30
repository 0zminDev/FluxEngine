#pragma once

#include "defines.h"

#include "logger.h"

namespace Flux::Core {
	class LoggerExtensions {
			ILogger* impl = nullptr;
		public:
			LoggerExtensions() = default;
			LoggerExtensions(ILogger* loggerImpl) : impl(loggerImpl) {}

			// TODO: Implement custom string
			EXPORT void Trace(const char* msg);
			EXPORT void Debug(const char* msg);
			EXPORT void Info(const char* msg);
			EXPORT void Warn(const char* msg);
			EXPORT void Error(const char* msg);
			EXPORT void Fatal(const char* msg);
	};
}
