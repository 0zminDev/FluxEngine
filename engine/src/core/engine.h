#pragma once
#include "logger/loggerExtensions.h"
#include "platform/platformManager.h"

namespace Flux::Core {
	class EXPORT Engine {
		public:
			Engine();
			~Engine();
			
			void init();
			
			LoggerExtensions* getLogger();

		private:
			Flux::Platform::PlatformManager* platformManager;
			Flux::Core::LoggerExtensions* logger;
	};
}