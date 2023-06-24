#include <GLRenderer/Resources/GLBufferResource.h>

using namespace ytr;

void GLBufferResource::incRefCount(){
	refCount++;
}

void GLBufferResource::decRefCount(){
	refCount--;
}

GLuint GLBufferResource::getVBO(){
	return vboHandle;
}

GLBufferResource::GLBufferResource(ResourceManager* man,GLuint name){
	vboHandle = name;
	this->man = man;
}
