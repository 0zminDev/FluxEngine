#include <catch2/catch_test_macros.hpp>
#include "export.h"

TEST_CASE("Logger Internal Access", "[logger]") {
    SECTION("Can access ILogger interface directly") {
        auto platformManager = std::make_unique<Flux::Platform::PlatformManager>();
        
        REQUIRE(platformManager != nullptr);
        
        platformManager->initLogger();
        
        auto* loggerImpl = platformManager->getLogger();
        REQUIRE(loggerImpl != nullptr);
        
        REQUIRE_NOTHROW(loggerImpl->log(Flux::Core::Types::Level::LOG_INFO, "Test message"));
    }
    
    SECTION("Can test LoggerExtensions wrapper") {
        Flux::Core::Engine engine;
        engine.init();
        
        auto* logger = engine.getLogger();
        REQUIRE(logger != nullptr);
        
        REQUIRE_NOTHROW(logger->Trace("Trace message"));
        REQUIRE_NOTHROW(logger->Debug("Debug message"));
        REQUIRE_NOTHROW(logger->Info("Info message"));
        REQUIRE_NOTHROW(logger->Warn("Warning message"));
        REQUIRE_NOTHROW(logger->Error("Error message"));
        REQUIRE_NOTHROW(logger->Fatal("Fatal message"));
    }
}

TEST_CASE("Platform Manager Internal Access", "[platform]") {
    SECTION("Can access platform manager internals") {
        auto platformManager = std::make_unique<Flux::Platform::PlatformManager>();
        
        REQUIRE(platformManager != nullptr);
        REQUIRE_NOTHROW(platformManager->initLogger());
        
        auto* logger = platformManager->getLogger();
        REQUIRE(logger != nullptr);
    }
}
