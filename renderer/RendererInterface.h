#pragma once
#include "ShaderManager.h"
#include "../Window/Window.h"
#include "../world/worldObject.h"
#include "Texture/TextureManager.h"

#include "../world/World.h"

namespace ytr{

	class RendererInterface{
		public:
			ShaderManager* shaderManager;
			TextureManager* textureManager;
			renderWindow* window;
			virtual void drawObject(worldObject* obj) = 0;
			virtual void initBuffers() = 0;
			virtual void renderFrame(World* world) = 0;
	};
}
