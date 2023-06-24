#pragma once
#include "../renderer/RendererInterface.h"
#include "../world/World.h"

namespace ytr{

	class GameLogic{
		public:
			virtual void setupLogic(RendererInterface* renderer,World* world) = 0;
			virtual void loop(double deltaTime) = 0;
			RendererInterface* renderer;
			World* world;
	};
}
