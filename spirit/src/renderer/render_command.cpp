#include "renderer/render_command.hpp"
#include "opengl/opengl_renderer_api.hpp"

namespace Spirit {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
