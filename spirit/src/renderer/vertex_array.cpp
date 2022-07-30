#include "renderer/vertex_array.hpp"
#include "renderer/renderer.hpp"
#include "opengl/opengl_vertex_array.hpp"

namespace Spirit {
	VertexArray* VertexArray::create() {
		switch (Renderer::getAPI()) {
			case RendererAPI::API::None:
				SPRT_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return new OpenGLVertexArray();
		}

		SPRT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
