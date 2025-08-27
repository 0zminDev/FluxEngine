#include "logger.h"
#include <iostream>

namespace Flux::Platform {
	void WindowsLogger::log(Flux::Core::Level level, const char* message) {
		std::cout << message << std::endl;
	}
}