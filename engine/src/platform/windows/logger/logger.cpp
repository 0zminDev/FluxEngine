#include "logger.h"
#include <memory>

namespace Flux::Platform {
	WindowsLogger::WindowsLogger() {
		// Set up default console scope and context
		auto consoleScope = addScope(Flux::Core::Types::Scope::CONSOLE);
		if (consoleScope) {
			currentScope = const_cast<Flux::Core::ILoggerScope*>(consoleScope);
			// Add and set a default console context
			currentScope->addContext("default");
			currentScope->setCurrentContext("default");
		}
	}

	WindowsLogger::~WindowsLogger() {
		// Clean up scopes
		for (auto* scope : scopes) {
			delete scope;
		}
		scopes.clear();
	}

	void WindowsLogger::log(Flux::Core::Types::Level level, const char* message) {
		// Log to current scope

		if(level >= Flux::Core::Types::Level::LOG_ERROR) {
			broadcast(level, message);
		} else {
			if (currentScope) {
				currentScope->log(level, message);
			} else {
				//TODO: IMPLEMENT ERROR HANDLING
			}
		}
	}

	void WindowsLogger::broadcast(Flux::Core::Types::Level level, const char *message) {
		// Go through all scopes and log
		for (const auto& scope : scopes) {
			scope->log(level, message);
		}
	}

	const Flux::Core::ILoggerScope *WindowsLogger::useScope(Flux::Core::Types::Scope scope) {
		if (scopeExists(scope)) {
			return getCurrentScope();
		} else {
			auto newScope = addScope(scope);
			return newScope;
		}
	}

	const Flux::Core::ILoggerScope *WindowsLogger::addScope(Flux::Core::Types::Scope scope) {
		if (scopeExists(scope)) return nullptr;
		// NOTE: Consider using smart pointers for scope management instead of creation and release and setting up to normal pointer
		auto newScope = createScope(scope);
		if (newScope) {
			scopes.push_back(newScope.release());
		}
		return scopes.back();
	}

	const Flux::Core::ILoggerScope *WindowsLogger::getCurrentScope() const {
		return currentScope;
	}
	bool WindowsLogger::scopeExists(Flux::Core::Types::Scope scope) const {
		// NOTE This is temporary cause it will be very unefficient make some allocator for this state possibly hashmap where
		// we can quickly check for existing scopes ID's 
		for (const auto& existingScope : scopes) {
			if (existingScope->getScopeID() == scope) {
				return true;
			}
		}
		return false;
	}
	std::unique_ptr<Flux::Core::ILoggerScope> WindowsLogger::createScope(Flux::Core::Types::Scope scope) const {
		std::unique_ptr<Flux::Core::ILoggerScope> newScope = nullptr;
		switch (scope) {
			case Flux::Core::Types::Scope::CONSOLE:
				newScope = std::make_unique<Flux::Platform::ConsoleScope>();
				break;
			
			default:
				break;
		}
		return newScope;
	}
}