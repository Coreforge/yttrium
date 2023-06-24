#pragma once

#include "ResourceManager.h"
#include "Resource.h"

#include <unordered_map>

namespace ytr{
class SimpleResourceManager : public ResourceManager{

public:

	Resource* getResource(RESOURCE_HANDLE_TYPE handle);
	void deleteResource(RESOURCE_HANDLE_TYPE handle);
	RESOURCE_HANDLE_TYPE createResource(Resource* data);
	void releaseResource(RESOURCE_HANDLE_TYPE handle);

private:
	std::unordered_map<RESOURCE_HANDLE_TYPE,Resource*> resources;
	RESOURCE_HANDLE_TYPE resCounter;
};
}
