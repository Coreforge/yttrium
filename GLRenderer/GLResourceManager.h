#pragma once

#include "../renderer/ResourceManager.h"

#include <stdint.h>
#include <map>
#include <shared_mutex>

namespace ytr{
class GLResourceManager : public ResourceManager{
public:
	Resource* getResource(RESOURCE_HANDLE_TYPE handle) override;
	void deleteResource(RESOURCE_HANDLE_TYPE handle) override;
	RESOURCE_HANDLE_TYPE createResource(Resource* data) override;

	void releaseResource(RESOURCE_HANDLE_TYPE handle) override;
	~GLResourceManager() override;

private:
	std::map<RESOURCE_HANDLE_TYPE, Resource*> resources;
	std::shared_mutex mapMutex;

	uint64_t resourceCounter;	// just count up the resource count to generate new handles. It's unlikely we'll ever run out of these, and if it happens, resources have very likely been freed again, so the handle can be reused

};
}
