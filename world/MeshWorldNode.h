#pragma once

#include "WorldNode.h"
#include "MeshBase.h"

namespace ytr{
class MeshWorldNode : public WorldNode{
public:
	MeshWorldNode(){
		type = NODE_MESH;
	}
	MeshBase* mesh;
};
}
