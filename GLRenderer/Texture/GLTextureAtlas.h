#pragma once
#include "../../renderer/Texture/TextureAtlas.h"
#include "../GLIncludes.h"
#include <unordered_map>

namespace ytr{

	class GLTextureAtlas : TextureAtlas{
		public:
			void initAtlas(int width, int height);
			void placeTexture(Texture* texture, const char* key);
			int testFit(int x, int y, int width, int height);   // test if Texture can fit at the specified location. All parameters are in Tiles.
			void uploadAtlas();  // Upload the current texture Atlas to the specified Texture on the GPU (binds Texture, so bindings are invalidated)
			//Texture* getTexture()
			int maxX;   // highest Tile currently used
			int maxY;
			GLuint ID;
		private:
			std::unordered_map<const char*, Texture*> map;
	};
}
