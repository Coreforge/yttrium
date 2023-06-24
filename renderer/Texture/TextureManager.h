#pragma once
#include "TextureAtlas.h"
#include <vector>

namespace ytr{

	enum textureType{
		TEXTURE_TYPE_ALBEDO,
		TEXTURE_TYPE_NORMAL
	};

	class TextureManager{
		public:
			std::vector<TextureAtlas*> atlas;
			virtual int addTexture(const char* key, int type, Texture* texture) = 0;
	};
}
