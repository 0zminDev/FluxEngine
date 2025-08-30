#pragma once

#include "core/logger/loggerScope.h"
#include "core/logger/types/loggerScope.h"

namespace Flux::Platform {
	class WindowsConsoleContext;
	
	class ConsoleScope : public Flux::Core::ILoggerScope {
			std::vector<WindowsConsoleContext*> consoleContexts;
			WindowsConsoleContext* currentContext = nullptr;
			Flux::Core::Types::Scope scopeID = Flux::Core::Types::Scope::CONSOLE;
		public:
			bool addContext(const std::string& identifier) override;
			void log(Flux::Core::Types::Level level, const char* message) override;
			bool setCurrentContext(const std::string& identifier) override;
			Flux::Core::Types::Scope getScopeID() const override;
		private:
			WindowsConsoleContext* createConsoleContext(const std::string& identifier);
			int contextExists(const std::string& identifier) const;
			void writeToConsole(HANDLE consoleHandle, const char* message);
    };
}