#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include "../Window/Window.h"

#include "../math/Transform.h"

namespace ytr{

	class Camera{
		public:
			Transform transform;

			// Offset of the actual camera from the origin
			glm::vec3 offset;
			float fov;
			float aspect;
			glm::mat4 projection;

			glm::mat4 renderMatrix;
			float nearClip;
			float farClip;
			//windowSettings* settings;
			void setupMatrices();

			void updateRenderMatrix();
	};
}
