#pragma once
#include "export.h"

namespace Flux::Core {
	class EXPORT Engine {
		public:
			Engine();
			~Engine();
			
			void init();
			
			Logger* getLogger();

		private:
			Flux::Platform::PlatformManager* platformManager;
			Flux::Core::Logger* logger;
	};
}