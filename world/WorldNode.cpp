#include "WorldNode.h"

#include <glm/glm.hpp>


using namespace ytr;

WorldNode::~WorldNode(){
	for(int i = 0; i < children.size(); i++){
		delete children[i];
	}
}

void WorldNode::addChild(WorldNode* node){
	children.emplace_back(node);
	node->parent = this;
}

WorldNode::WorldNode(){
	transform.position = glm::vec3(0.0,0.0,0.0);
	transform.rotation = glm::vec3(0.0,0.0,0.0);
	transform.scale = glm::vec3(1.0,1.0,1.0);
	parent = nullptr;
	type = NODE_REGULAR;
}
