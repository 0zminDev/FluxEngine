#include <iostream>
#include <FluxEngine.h>

int main() {
    Flux::Core::Engine engine;
    engine.init();

    auto* logger = engine.getLogger();
    logger->Error("Something broke");
    logger->Warn("Low memory");
    logger->Info("Loading completed");
    return 0;
}
