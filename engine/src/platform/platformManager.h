#pragma once 
#include <memory>

#include "defines.h"
#include "core/logger/logger.h"

namespace Flux::Platform {
	class PlatformManager {
		public:
			void initLogger();
			Flux::Core::ILogger* getLogger() const;
		private:
			std::unique_ptr<Flux::Core::ILogger> logger;
	};
}