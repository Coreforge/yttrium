#pragma once
#include "../renderer/ShaderManager.h"
#include <unordered_map>

#include "GLIncludes.h"

namespace ytr{

	class GLShaderManager : ShaderManager{
		public:
			int addShader(const char* key,const char* vertex, const char* fragment);
			Shader* getShader(const char* key);

			static GLuint createShaderProgram(const char* vertex, const char* fragment);
		private:
			std::unordered_map<const char*,Shader*> shaders;
	};
}
