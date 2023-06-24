#include "SimpleResourceManager.h"

using namespace ytr;

Resource* SimpleResourceManager::getResource(RESOURCE_HANDLE_TYPE handle){
	if(resources.count(handle) == 0){
		return nullptr;
	}
	return resources[handle];
}

void SimpleResourceManager::deleteResource(RESOURCE_HANDLE_TYPE handle){

}

RESOURCE_HANDLE_TYPE SimpleResourceManager::createResource(Resource* data){
	// potential for an infinite loop, but it's unlikely
	while(resources.count(resCounter) != 0){
		resCounter++;
	}
	resources.insert({resCounter,data});
	data->manager = this;
	data->handle = resCounter;
	return resCounter;
}

void SimpleResourceManager::releaseResource(RESOURCE_HANDLE_TYPE handle){
	if(resources.count(handle) == 0){
		return;
	}
	resources[handle]->decRefCount();
}
