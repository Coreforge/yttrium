#pragma once

#include <vector>
#include <glm/vec4.hpp>
#include "Mesh.h"
#include "../math/types.h"

namespace ytr{

	class worldObject{
		public:
			std::vector<Mesh*> meshes;
			worldObject* parent;
			std::vector<worldObject*> children;
			glm::vec4 position;
			glm::vec4 rotation;
			glm::vec4 scale;
	};
}
