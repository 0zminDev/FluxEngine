#include <iostream>
#include <FluxEngine.h>

int main() {
    std::cout << "Starting FluxEngine Sandbox..." << std::endl;
    
    Flux::Core::Engine engine;
    engine.init();

    // Get a logger with Sandbox context (same instance, different context)
    auto* sandboxLogger = engine.getLogger("Sandbox");
    
    sandboxLogger->Error("Something broke");
    sandboxLogger->Warn("Low memory");
    sandboxLogger->Info("Loading completed");
    
    // No need to delete - it's the same instance as engine logger
    
    std::cout << "Sandbox execution complete." << std::endl;
    return 0;
}
