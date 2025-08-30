#pragma once

#include <string>
#include "core/logger/loggerContext.h"

namespace Flux::Platform {
    template<typename T>
    class ILoggerPlatformContext : public Flux::Core::ILoggerContext {
			T* handle;
			std::string identifier;
		public:
			explicit ILoggerPlatformContext(T* h, const std::string& id) : handle(h), identifier(id) {}

			bool isValid() const override { return handle != nullptr; }
			const std::string& getIdentifier() const override { return identifier; }

			T* getHandle() const { return handle; }
    };
}