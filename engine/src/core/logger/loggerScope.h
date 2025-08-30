#pragma once

#include <string>

#include "defines.h"

#include "loggerContext.h"
#include "types/loggerLevel.h"

namespace Flux::Core {
	class ILoggerScope {
		public:
			virtual ~ILoggerScope() = default;
			virtual void log(Types::Level level, const char* message) = 0;
			virtual bool addContext(const std::string& identifier) = 0;
			virtual bool setCurrentContext(const std::string& identifier) = 0;
			virtual Types::Scope getScopeID() const = 0;
	};
}