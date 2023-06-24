#pragma once
#include "TextureTile.h"
#include <vector>

namespace ytr{

	class TextureAtlas;

	class Texture{
		public:
			int width;
			int height;
			std::vector<TextureTile> tiles;
			int format;
			TextureAtlas* atlas;
			enum formats{
				TEXTURE_RGBA
			};
	};
}
