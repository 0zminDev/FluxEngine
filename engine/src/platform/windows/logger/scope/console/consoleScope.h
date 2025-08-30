#pragma once

#include "core/logger/loggerScope.h"
#include "core/logger/types/loggerScope.h"
#include "core/logger/formatters/ConsoleFormatter.h"
#include <vector>
#include <memory>

namespace Flux::Platform {
	class WindowsConsoleContext;
	
	class ConsoleScope : public Flux::Core::ILoggerScope {
			std::vector<WindowsConsoleContext*> consoleContexts;
			WindowsConsoleContext* currentContext = nullptr;
			Flux::Core::Types::Scope scopeID = Flux::Core::Types::Scope::CONSOLE;
			std::unique_ptr<Flux::Core::Formatters::ConsoleFormatter> formatter;
		public:
			ConsoleScope();
			~ConsoleScope();
			
			bool addContext(const std::string& identifier) override;
			void log(Flux::Core::Types::Level level, const char* message) override;
			void log(Flux::Core::Types::Level level, const char* message, const char* systemContext) override;
			bool setCurrentContext(const std::string& identifier) override;
			Flux::Core::Types::Scope getScopeID() const override;
			
			// Configuration methods
			void setFormatter(std::unique_ptr<Flux::Core::Formatters::ConsoleFormatter> newFormatter);
			Flux::Core::Formatters::ConsoleFormatter* getFormatter() const;
			
		private:
			WindowsConsoleContext* createConsoleContext(const std::string& identifier);
			int contextExists(const std::string& identifier) const;
			void writeToConsole(Flux::Core::Types::Level level, const char* message, const char* systemContext = nullptr);
    };
}