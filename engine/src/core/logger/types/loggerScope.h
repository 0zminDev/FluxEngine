#pragma once

namespace Flux::Core::Types {
	typedef enum Scope {
		CONSOLE,
		FILE,
		UI,
		API,
		Broadcast
	} Scope;
}