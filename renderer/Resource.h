#pragma once
#include <stdint.h>

namespace ytr{
class ResourceManager;
class Resource{
public:
	virtual ~Resource(){

	}
	virtual void incRefCount() = 0;
	virtual void decRefCount() = 0;
	int refCount = 0;
	ResourceManager* manager;

	// WARNING: this ignores the config in ResourceManager.h, so this can cause problems!
	uint32_t handle;
};
}
