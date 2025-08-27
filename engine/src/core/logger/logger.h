#pragma once
#include "defines.h"
#include <cstdio>

namespace Flux::Core {
	typedef enum Level {
		LEVEL_TRACE,
		LEVEL_DEBUG,
		LEVEL_INFO,
		LEVEL_WARN,
		LEVEL_ERROR,
		LEVEL_FATAL
	} Level;

	typedef enum Color {
		COLOR_DEFAULT,
		COLOR_RED,
		COLOR_GREEN,
		COLOR_BLUE,
		COLOR_YELLOW,
		COLOR_CYAN,
		COLOR_MAGENTA
	} Color;

	class ILogger {
		public:
			virtual void log(Level level, Color color, const char* message) = 0;
			virtual ~ILogger() = default;
	};

	class Logger {
			ILogger* impl = nullptr;
		public:
			Logger() = default;
			Logger(ILogger* loggerImpl) : impl(loggerImpl) {}

			// TODO: Implement custom string
			EXPORT void Trace(const char* msg);
			EXPORT void Debug(const char* msg);
			EXPORT void Info(const char* msg);
			EXPORT void Warn(const char* msg);
			EXPORT void Error(const char* msg);
			EXPORT void Fatal(const char* msg);
	};
}