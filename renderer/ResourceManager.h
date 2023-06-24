#pragma once

#include <vector>
#include <stdint.h>

#include "Resource.h"

#define RESOURCE_HANDLE_TYPE uint32_t

namespace ytr{
class ResourceManager{
public:

	// increases the refCount
	virtual Resource* getResource(RESOURCE_HANDLE_TYPE handle) = 0;
	virtual void deleteResource(RESOURCE_HANDLE_TYPE handle) = 0;
	virtual RESOURCE_HANDLE_TYPE createResource(Resource* data) = 0;
	// lowers the refcount
	virtual void releaseResource(RESOURCE_HANDLE_TYPE handle) = 0;
	virtual ~ResourceManager(){

	}
};

}
