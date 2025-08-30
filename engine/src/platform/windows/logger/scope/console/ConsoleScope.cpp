#include "../../data/consoleContext.h"
#include "consoleScope.h"
#include <algorithm>
#include <vector>
#include <cstdio>
#include <string>

namespace Flux::Platform {
    void ConsoleScope::log(Flux::Core::Types::Level level, const char* message) {
        if (currentContext) {
            writeToConsole(currentContext->getConsoleHandle(), message);
        }
    }

    bool ConsoleScope::addContext(const std::string& identifier) {
        WindowsConsoleContext *context = createConsoleContext(identifier);
        if (context) {
            consoleContexts.push_back(context);
            return true;
        }
        return false;
    }

    bool ConsoleScope::setCurrentContext(const std::string& identifier) {
        int contextIndex = contextExists(identifier);
        if (contextIndex >= 0) {
            currentContext = consoleContexts[contextIndex];
            return true;
        } else {
            bool added = addContext(identifier);
            if (added) {
                currentContext = consoleContexts.back();
                return true;
            }
            return false;
        }
    }

    Flux::Core::Types::Scope ConsoleScope::getScopeID() const
    {
        return scopeID;
    }
	WindowsConsoleContext *ConsoleScope::createConsoleContext(const std::string &identifier)
	{
		if (contextExists(identifier) == -1) {
            #if PLATFORM_WINDOWS
                HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
                
                if (consoleHandle == INVALID_HANDLE_VALUE) {
                    AllocConsole();
                    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
                }

                if (consoleHandle != INVALID_HANDLE_VALUE) {
                    return new WindowsConsoleContext(consoleHandle, identifier);
                }
            #endif
        }
        return nullptr;
	}
	int ConsoleScope::contextExists(const std::string &identifier) const
	{
        // NOTE: This is suboptimal we want hashmap and conflict check so it will be more optimalized
		for (const auto& context : consoleContexts) {
			if (context->getIdentifier() == identifier) {
				return std::distance(consoleContexts.begin(), std::find(consoleContexts.begin(), consoleContexts.end(), context));
			}
		}
		return -1;
	}
	void ConsoleScope::writeToConsole(HANDLE consoleHandle, const char *message)
	{
		if (consoleHandle != INVALID_HANDLE_VALUE && message) {
			DWORD bytesWritten;
			std::string messageWithNewline = std::string(message) + "\n";
			WriteConsoleA(consoleHandle, messageWithNewline.c_str(), 
				static_cast<DWORD>(messageWithNewline.length()), &bytesWritten, nullptr);
		}
	}
}
