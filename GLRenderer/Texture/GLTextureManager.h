#pragma once
#include "../../renderer/Texture/TextureManager.h"
#include "GLTextureAtlas.h"

namespace ytr{

	class GLTextureManager : TextureManager{
		public:
			GLTextureAtlas* albedo;
			GLTextureAtlas* normal;
			bool valid;
			void update();
			void init(int size);
			int addTexture(const char* key, int type, Texture* texture);
	};
}
