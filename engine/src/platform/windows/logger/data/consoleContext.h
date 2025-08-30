#pragma once
#include "platform/loggerPlatformContext.h"
#include "platformExport.h"

namespace Flux::Platform {
	class WindowsConsoleContext : public ILoggerPlatformContext<void> {
			HANDLE consoleHandle;
			std::string identifier;
		public:
			explicit WindowsConsoleContext(HANDLE h, const std::string& id) : ILoggerPlatformContext<void>(h, id), consoleHandle(h), identifier(id) {}
			HANDLE getConsoleHandle() const { return consoleHandle; }
			const std::string& getIdentifier() const override { return identifier; }
			void setConsoleHandle(HANDLE h) { consoleHandle = h; }
	};
}