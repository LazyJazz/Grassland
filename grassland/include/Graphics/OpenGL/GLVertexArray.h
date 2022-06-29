#pragma once
#include "GLHeader.h"

namespace Grassland
{
	typedef int32_t GRL_OPENGL_BUFFER_USAGE;
#define GRL_OPENGL_BUFFER_USAGE_STATIC 1
#define GRL_OPENGL_BUFFER_USAGE_DYNAMIC 2
#define GRL_OPENGL_BUFFER_USAGE_STREAM 3
	namespace Graphics
	{
		namespace OpenGL
		{
			class VertexArray
			{
			public:
				VertexArray();
				~VertexArray();
				void BindVerticesData(void * vertices_data, int32_t data_count, GRL_OPENGL_BUFFER_USAGE usage);
				void BindIndicesData(void* indices_data, int32_t data_count, GRL_OPENGL_BUFFER_USAGE usage);
				void ActiveVerticesLayout(int32_t slot, int32_t bundle_size, GRL_TYPE bundle_type, int32_t stride, int32_t offset);
				void EnableSlot(int32_t slot);
				void DisableSlot(int32_t slot);
				void Render();
			private:
				uint32_t __vertex_array_object;
				uint32_t __vertex_buffer_object;
				uint32_t __element_buffer_object;
				int32_t __indices_cnt;
			};
		}
	}

	class GRLIOpenGLVertexArray : public GRLIBase
	{
	public:
		virtual void BindVerticesData(void* vertices_data, int32_t data_count, GRL_OPENGL_BUFFER_USAGE usage) = 0;
		virtual void BindIndicesData(void* indices_data, int32_t data_count, GRL_OPENGL_BUFFER_USAGE usage) = 0;
		virtual void ActiveVerticesLayout(int32_t slot, int32_t bundle_size, uint32_t bundle_type, int32_t stride, int32_t offset) = 0;
		virtual void EnableSlot(int32_t slot) = 0;
		virtual void DisableSlot(int32_t slot) = 0;
		virtual void Render() = 0;
	};

	GRL_RESULT GRLCreateOpenGLVertexArray(GRLIOpenGLVertexArray ** ppVertexArray);
}