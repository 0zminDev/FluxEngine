#include <iostream>
#include <FluxEngine.h>

int main() {
    std::cout << "Starting FluxEngine Sandbox..." << std::endl;
    
    Flux::Core::Engine engine;
    engine.init();

    auto* logger = engine.getLogger();
    
    logger->Error("Something broke");
    logger->Warn("Low memory");
    logger->Info("Loading completed");
    
    std::cout << "Sandbox execution complete." << std::endl;
    return 0;
}
