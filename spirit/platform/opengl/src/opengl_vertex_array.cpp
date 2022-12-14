#include "opengl/opengl_vertex_array.hpp"
#include <GL/glew.h>

namespace Spirit {
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type) {
			case Spirit::ShaderDataType::Float:    return GL_FLOAT;
			case Spirit::ShaderDataType::Float2:   return GL_FLOAT;
			case Spirit::ShaderDataType::Float3:   return GL_FLOAT;
			case Spirit::ShaderDataType::Float4:   return GL_FLOAT;
			case Spirit::ShaderDataType::Mat3:     return GL_FLOAT;
			case Spirit::ShaderDataType::Mat4:     return GL_FLOAT;
			case Spirit::ShaderDataType::Int:      return GL_INT;
			case Spirit::ShaderDataType::Int2:     return GL_INT;
			case Spirit::ShaderDataType::Int3:     return GL_INT;
			case Spirit::ShaderDataType::Int4:     return GL_INT;
			case Spirit::ShaderDataType::Bool:     return GL_BOOL;
		}

		SPRT_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::bind() const {
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::unbind() const {
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
		SPRT_CORE_ASSERT(vertexBuffer->getLayout().getElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->getLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.getStride(),
				(const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
		glBindVertexArray(m_RendererID);
		indexBuffer->bind();

		m_IndexBuffer = indexBuffer;
	}
}
