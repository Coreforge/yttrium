#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "../math/Transform.h"

namespace ytr{
class WorldNode{
public:
	enum Type{
		NODE_ROOT,
		NODE_REGULAR,	// this node does nothing, it just holds more nodes
		NODE_MESH		// a mesh to render
	};
	int type;
	std::vector<WorldNode*> children;
	WorldNode* parent;


	// the whole transform
	/*glm::vec4 position;
	glm::vec4 rotation;
	glm::vec4 scale;*/
	Transform transform;

	void addChild(WorldNode* node);
	~WorldNode();
	WorldNode();
};
}
