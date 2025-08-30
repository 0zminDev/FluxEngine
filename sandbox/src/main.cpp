#include <iostream>
#include <FluxEngine.h>

int main() {
    std::cout << "Starting FluxEngine Sandbox..." << std::endl;
    
    Flux::Core::Engine engine;
    engine.init();

    // Use RAII scoped context - automatically restores original context
    {
        auto scopedLogger = engine.getLogger()->withContext("Sandbox");
        scopedLogger.Error("Something broke");
        scopedLogger.Warn("Low memory");
        scopedLogger.Info("Loading completed");
    } // Original context automatically restored here

    {
        auto scopedLogger = engine.getLogger()->withContext("Sandbox2");
        scopedLogger.Error("Something broke");
        scopedLogger.Warn("Low memory");
        scopedLogger.Info("Loading completed");
    } // Original context automatically restored here
    
    {
        auto* scopedLogger = engine.getLogger();
        scopedLogger->Error("Something broke");
        scopedLogger->Warn("Low memory");
        scopedLogger->Info("Loading completed");
    } // Original context automatically restored here

    // Engine context is restored
    engine.getLogger()->Info("Sandbox execution complete");
    
    std::cout << "Sandbox execution complete." << std::endl;
    return 0;
}
