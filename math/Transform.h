#pragma once

#include <glm/glm.hpp>

namespace ytr{
class Transform{
public:
	glm::vec3 position;

	/*
	 * X: Pitch
	 * Y: Yaw
	 * Z: Roll
	 */
	glm::vec3 rotation;
	glm::mat4 rotationMat;
	enum rotationType{
		ROTATION_EULER,
		ROTATION_MATRIX
	} rotationType = ROTATION_EULER;
	glm::vec3 scale;
};
}
