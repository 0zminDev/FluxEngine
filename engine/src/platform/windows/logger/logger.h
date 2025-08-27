#pragma once 
#include "export.h"

namespace Flux::Platform {
	class EXPORT WindowsLogger : public Flux::Core::ILogger {
		public:
			void log(Flux::Core::Level level, const char* message) override;
	};
}