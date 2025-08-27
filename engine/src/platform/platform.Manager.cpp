#include "platformManager.h"
#include "export.h"

namespace Flux::Platform {
	void PlatformManager::initLogger() {
		#if CURRENT_PLATFORM == PLATFORM_WINDOWS
			logger = std::make_unique<WindowsLogger>();
		#elif CURRENT_PLATFORM == PLATFORM_ANDROID
			logger = std::make_unique<AndroidLogger>();
		#endif
	}
	
	Flux::Core::ILogger* PlatformManager::getLogger() const { 
		return logger.get(); 
	}
}