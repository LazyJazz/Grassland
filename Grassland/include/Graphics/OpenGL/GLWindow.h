#pragma once

#include "GLHeader.h"

namespace Grassland
{
	namespace Graphics
	{
		namespace OpenGL
		{
			GRL_RESULT Initilize(int32_t width, int32_t height, const char* window_title, bool full_screen = false);

			/*
			@return Return the GLFW window handle, not suggested to use.
			*/
			GLFWwindow* GetGLFWWindow();

			GRL_RESULT Terminate();


		}
	}

	GRL_RESULT GRLOpenGLInit(int32_t width, int32_t height, const char* window_title, bool full_screen = false);

	GRL_RESULT GRLOpenGLTerminate();
}