#pragma once

#include "core/app_spec.hpp"

namespace Spirit {
	class GraphicsContext {
	public:
		virtual void Init(ApplicationCommandLineArgs& args) = 0;
		virtual void SwapBuffers() = 0;
	};
}
