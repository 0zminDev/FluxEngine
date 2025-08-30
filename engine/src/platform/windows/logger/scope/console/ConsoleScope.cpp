#include "../../data/consoleContext.h"
#include "consoleScope.h"
#include <algorithm>
#include <vector>
#include <cstdio>
#include <string>

namespace Flux::Platform {

    ConsoleScope::ConsoleScope() 
        : formatter(std::make_unique<Flux::Core::Formatters::ConsoleFormatter>()) {
    }
    
    ConsoleScope::~ConsoleScope() {
        for (auto* context : consoleContexts) {
            delete context;
        }
        consoleContexts.clear();
    }

    void ConsoleScope::log(Flux::Core::Types::Level level, const char* message) {
        if (currentContext) {
            writeToConsole(level, message);
        }
    }
    
    void ConsoleScope::log(Flux::Core::Types::Level level, const char* message, const char* systemContext) {
        if (currentContext) {
            writeToConsole(level, message, systemContext);
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
	void ConsoleScope::writeToConsole(Flux::Core::Types::Level level, const char *message, const char* systemContext)
	{
		if (currentContext && currentContext->getConsoleHandle() != INVALID_HANDLE_VALUE && message && formatter) {
			// Create log entry
			Flux::Core::Formatters::LogEntry entry;
			entry.level = level;
			entry.message = message;
			entry.systemContext = systemContext;
			entry.timestamp = nullptr; // Formatter will generate its own timestamp
			
			// Format the message
			std::string formattedMessage = formatter->format(entry);
			
			// Write to console
			DWORD bytesWritten;
			WriteConsoleA(currentContext->getConsoleHandle(), formattedMessage.c_str(), 
				static_cast<DWORD>(formattedMessage.length()), &bytesWritten, nullptr);
		}
	}
	
	void ConsoleScope::setFormatter(std::unique_ptr<Flux::Core::Formatters::ConsoleFormatter> newFormatter) {
		formatter = std::move(newFormatter);
	}
	
	Flux::Core::Formatters::ConsoleFormatter* ConsoleScope::getFormatter() const {
		return formatter.get();
	}
}
