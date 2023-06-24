#pragma once

#include "../math/types.h"
#include <vector>
#include <memory>
#include <glm/vec4.hpp>
#include "Region.h"
#include "WorldNode.h"

#include "../renderer/Camera.h"

namespace ytr{

	class World{
		public:
			World(){
				rootNode = new WorldNode();
			}
			//Camera camera;
			WorldNode* rootNode;
			//std::vector<WorldNode*> nodes;
	};
}
