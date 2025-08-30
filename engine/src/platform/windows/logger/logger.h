#pragma once 

#include <vector>

#include "defines.h"
#include "platformExport.h"
#include "core/logger/logger.h"
#include "core/logger/loggerScope.h"
#include "platform/windows/logger/scope/console/consoleScope.h"

namespace Flux::Platform {
	class WindowsLogger : public Flux::Core::ILogger {
			std::vector<Flux::Core::ILoggerScope*> scopes;
			Flux::Core::ILoggerScope* currentScope = nullptr;
		public:
			WindowsLogger(); // Constructor to set up default console scope
			~WindowsLogger(); // Destructor to clean up scopes
			void log(Flux::Core::Types::Level level, const char* message) override; // TODO: Implement context based log
			void broadcast(Flux::Core::Types::Level level, const char* message) override;

			const Flux::Core::ILoggerScope* useScope(Flux::Core::Types::Scope scope) override;
			const Flux::Core::ILoggerScope* addScope(Flux::Core::Types::Scope scope) override;
			const Flux::Core::ILoggerScope* getCurrentScope() const override;
		private:
			bool scopeExists(Flux::Core::Types::Scope scope) const override;
			std::unique_ptr<Flux::Core::ILoggerScope> createScope(Flux::Core::Types::Scope scope) const override;
	};
}