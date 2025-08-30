#pragma once

#include "defines.h"

#include "logger.h"

namespace Flux::Core {
	class ILoggerContext {
		public:
			virtual ~ILoggerContext() = default;
			virtual bool isValid() const = 0;
			virtual const std::string& getIdentifier() const = 0;
	};
}
