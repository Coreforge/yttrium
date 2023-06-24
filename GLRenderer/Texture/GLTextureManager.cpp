#include "GLTextureManager.h"
#include "../../renderer/Texture/Texture.h"

using namespace ytr;

void GLTextureManager::init(int size){
    albedo = new GLTextureAtlas;
    albedo->initAtlas(size,size);
    ((TextureAtlas*)albedo)->bytesPerPixel = 4;  // RGBA
    ((TextureAtlas*)albedo)->format = Texture::formats::TEXTURE_RGBA;

}

int GLTextureManager::addTexture(const char* key, int type, Texture* texture){
    if(type == TEXTURE_TYPE_ALBEDO){
        albedo->placeTexture(texture,key);
        valid = false;
    }
    return 0;
}

void GLTextureManager::update(){
    albedo->uploadAtlas();
    valid=true;
}
