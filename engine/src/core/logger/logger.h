#pragma once

#include "defines.h"
#include "types/loggerScope.h"
#include "loggerScope.h"
#include <memory>

namespace Flux::Core {
	class ILogger {
		protected:
			std::string systemContext = "Unknown";
			
		public:
			virtual ~ILogger() = default;

			virtual void log(Types::Level level, const char* message) = 0;
			virtual void broadcast(Types::Level level, const char* message) = 0;

			virtual const ILoggerScope* useScope(Types::Scope scope) = 0;
			virtual const ILoggerScope* addScope(Types::Scope scope) = 0;
			virtual const ILoggerScope* getCurrentScope() const = 0;
			
			virtual void setSystemContext(const std::string& context) { systemContext = context; }
			virtual const std::string& getSystemContext() const { return systemContext; }

		private:
			virtual bool scopeExists(Types::Scope scope) const = 0;
			virtual std::unique_ptr<ILoggerScope> createScope(Types::Scope scope) const = 0;
	};
}

// TODO: Consider implementing removal of stale scopes/contexts