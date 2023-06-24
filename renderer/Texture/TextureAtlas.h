#pragma once

#include "TextureTile.h"
#include "Texture.h"

namespace ytr{

	class TextureAtlas{
		public:
			TextureTile** tiles;
			int width;
			int height;
			int bytesPerPixel;
			virtual void initAtlas(int width, int height) = 0;
			virtual void placeTexture(Texture* texture, const char* key) = 0;
			virtual void uploadAtlas() = 0;
			//virtual void getTexture(const char* key) = 0;
			int format;
			bool valid; // true if the current data in the tiles represents the data on the GPU (uploading the textures every frame would be very slow)
	};
}
