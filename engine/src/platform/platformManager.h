#pragma once 
#include "defines.h"
#include <memory>

#include "core/logger/logger.h"

namespace Flux::Platform {
	class EXPORT PlatformManager {
		public:
			void initLogger();
			Flux::Core::ILogger* getLogger() const;
		private:
			std::unique_ptr<Flux::Core::ILogger> logger;
	};
}