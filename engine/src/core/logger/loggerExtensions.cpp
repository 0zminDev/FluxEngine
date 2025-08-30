#include "loggerExtensions.h"

#include "export.h"
#include "types.h"

// TODO: Implement broadcast logging versions
namespace Flux::Core {
	void LoggerExtensions::Trace(const char* msg) {
		logWithContext(Types::Level::LOG_TRACE, msg);
	}

	void LoggerExtensions::Debug(const char* msg) {
		logWithContext(Types::Level::LOG_DEBUG, msg);
	}

	void LoggerExtensions::Info(const char* msg) {
		logWithContext(Types::Level::LOG_INFO, msg);
	}

	void LoggerExtensions::Warn(const char* msg) {
		logWithContext(Types::Level::LOG_WARN, msg);
	}
    // TODO: Implements broadcast as default and only way of logging error and higher level logs
	void LoggerExtensions::Error(const char* msg) {
		logWithContext(Types::Level::LOG_ERROR, msg);
	}

	void LoggerExtensions::Fatal(const char* msg) {
		logWithContext(Types::Level::LOG_FATAL, msg);
	}
	
	void LoggerExtensions::logWithContext(Types::Level level, const char* msg) {
		if (impl) {
			// Temporarily set system context if we have one
			std::string originalContext;
			bool hasContext = !systemContext.empty();
			if (hasContext) {
				originalContext = impl->getSystemContext();
				impl->setSystemContext(systemContext);
			}
			
			impl->log(level, msg);
			
			// Restore original context
			if (hasContext) {
				impl->setSystemContext(originalContext);
			}
		} else {
			// TODO: Implement Error Handling
		}
	}
}