#include "GLResourceManager.h"

using namespace ytr;

RESOURCE_HANDLE_TYPE GLResourceManager::createResource(Resource* data){
	RESOURCE_HANDLE_TYPE handle = -1;
	if(handle == -1){
	resourceCounter++;
	// in theory this could cause an endless loop, but in practice it won't
		while(resources.count(resourceCounter) != 0) resourceCounter++;
		handle = resourceCounter;
	} else {
		while(resources.count(handle) != 0) handle++;
	}
	mapMutex.lock();
	resources.insert({handle, data});
	data->incRefCount();
	mapMutex.unlock();
	return handle;
}

void GLResourceManager::deleteResource(RESOURCE_HANDLE_TYPE handle){

}

Resource* GLResourceManager::getResource(RESOURCE_HANDLE_TYPE handle){
	if(resources.count(handle) > 0){
		return resources[handle];
	}
	return nullptr;
}

GLResourceManager::~GLResourceManager(){

}

void GLResourceManager::releaseResource(RESOURCE_HANDLE_TYPE handle){
	if(resources.count(handle) > 0){
		resources[handle]->decRefCount();
	}
}
