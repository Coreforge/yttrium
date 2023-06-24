#pragma once
#include "Shader.h"

namespace ytr{

	class ShaderManager{
		public:
			virtual int addShader(const char* key,const char* vertex, const char* fragment) = 0;
			virtual Shader* getShader(const char* key) = 0;
	};
}
