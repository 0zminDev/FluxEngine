#include "logger.h"

namespace Flux::Core {
	void Logger::Trace(const char* msg) {
		if (impl) {
            const char* enhancedMsg = msg;
            impl->log(Level::LEVEL_TRACE, Color::COLOR_DEFAULT, enhancedMsg);
        } else {
            // TODO: Implement Error Handling
        }
	}

	void Logger::Debug(const char* msg) {
		if (impl) {
            const char* enhancedMsg = msg; // TODO: Add timestamp or other enhancements
            impl->log(Level::LEVEL_DEBUG, Color::COLOR_BLUE, enhancedMsg);
        } else {
            // TODO: Implement Error Handling
        }
	}

	void Logger::Info(const char* msg) {
		if (impl) {
            const char* enhancedMsg = msg; // TODO: Add timestamp or other enhancements
            impl->log(Level::LEVEL_INFO, Color::COLOR_GREEN, enhancedMsg);
        } else {
            // TODO: Implement Error Handling
        }
	}

	void Logger::Warn(const char* msg) {
		if (impl) {
            const char* enhancedMsg = msg; // TODO: Add timestamp or other enhancements
            impl->log(Level::LEVEL_WARN, Color::COLOR_YELLOW, enhancedMsg);
        } else {
            // TODO: Implement Error Handling
        }
	}

	void Logger::Error(const char* msg) {
		if (impl) {
            const char* enhancedMsg = msg; // TODO: Add timestamp or other enhancements
            impl->log(Level::LEVEL_ERROR, Color::COLOR_RED, enhancedMsg);
        } else {
            // TODO: Implement Error Handling
        }
	}

	void Logger::Fatal(const char* msg) {
		if (impl) {
            const char* enhancedMsg = msg; // TODO: Add timestamp or other enhancements
            impl->log(Level::LEVEL_FATAL, Color::COLOR_MAGENTA, enhancedMsg);
        } else {
            // TODO: Implement Error Handling
        }
	}
}