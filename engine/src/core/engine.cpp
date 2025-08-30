#include "engine.h"

namespace Flux::Core {
	Engine::Engine() {
		platformManager = new Flux::Platform::PlatformManager();
		logger = nullptr;
	}
	
	Engine::~Engine() {
		delete platformManager;
		delete logger;
	}

	void Engine::init() {
		platformManager->initLogger();
		logger = new LoggerExtensions(platformManager->getLogger());
		platformManager->getLogger()->setSystemContext("Engine");
		
		logger->Info("Engine initialized.");
	}

	LoggerExtensions* Engine::getLogger() {
		return logger;
	}
	
	LoggerExtensions* Engine::getLogger(const std::string& systemContext) {
		logger->setSystemContext(systemContext);
		return logger;
	}
}