#pragma once
#include "../renderer/RendererInterface.h"
#include "GLIncludes.h"
#include "../world/World.h"

namespace ytr{


	class GLRenderer : RendererInterface{
		public:
			void drawObject(worldObject* obj);
			void initBuffers();
			void renderFrame(World* world);
			GLRenderer();
			Camera* cam;
		private:

			void renderNode(WorldNode* node);
			GLuint meshVBO;
			GLuint meshVAO;
	};
}
