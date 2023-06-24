#pragma once
#include "../../renderer/Resource.h"
#include "../../renderer/ResourceManager.h"

#include "../GLIncludes.h"

namespace ytr{
class GLBufferResource : public Resource{
public:
	GLBufferResource(ResourceManager* man, GLuint name);
	void incRefCount() override;
	void decRefCount() override;

	GLuint getVBO();

private:
	GLuint vboHandle;
	ResourceManager* man;
};
}
