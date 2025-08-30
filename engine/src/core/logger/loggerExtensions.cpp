#include "loggerExtensions.h"

#include "export.h"
#include "types.h"

// TODO: Implement broadcast logging versions
namespace Flux::Core {
	void LoggerExtensions::Trace(const char* msg) {
		if (impl) {
            const char* enhancedMsg = msg;
            impl->log(Types::Level::LOG_TRACE, enhancedMsg);
        } else {
            // TODO: Implement Error Handling
        }
	}

	void LoggerExtensions::Debug(const char* msg) {
		if (impl) {
            const char* enhancedMsg = msg; // TODO: Add timestamp or other enhancements
            impl->log(Types::Level::LOG_DEBUG, enhancedMsg);
        } else {
            // TODO: Implement Error Handling
        }
	}

	void LoggerExtensions::Info(const char* msg) {
		if (impl) {
            const char* enhancedMsg = msg; // TODO: Add timestamp or other enhancements
            impl->log(Types::Level::LOG_INFO, enhancedMsg);
        } else {
            // TODO: Implement Error Handling
        }
	}

	void LoggerExtensions::Warn(const char* msg) {
		if (impl) {
            const char* enhancedMsg = msg; // TODO: Add timestamp or other enhancements
            impl->log(Types::Level::LOG_WARN, enhancedMsg);
        } else {
            // TODO: Implement Error Handling
        }
	}
    // TODO: Implements broadcast as default and only way of logging error and higher level logs
	void LoggerExtensions::Error(const char* msg) {
		if (impl) {
            const char* enhancedMsg = msg; // TODO: Add timestamp or other enhancements
            impl->log(Types::Level::LOG_ERROR, enhancedMsg);
        } else {
            // TODO: Implement Error Handling
        }
	}

	void LoggerExtensions::Fatal(const char* msg) {
		if (impl) {
            const char* enhancedMsg = msg; // TODO: Add timestamp or other enhancements
            impl->log(Types::Level::LOG_FATAL, enhancedMsg);
        } else {
            // TODO: Implement Error Handling
        }
	}
}