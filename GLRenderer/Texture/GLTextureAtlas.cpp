#include "GLTextureAtlas.h"
#include <memory>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace ytr;

void GLTextureAtlas::initAtlas(int width, int height){
    this->width = width;
    this->height = height;
    int numTiles = width * height;
    tiles = (TextureTile**)calloc(numTiles,sizeof(TextureTile*));
    printf("before init memset\n");
    memset(tiles,0,numTiles * sizeof(TextureTile*));
    printf("after init memset\n");
    glGenTextures(1,&ID);
}

int GLTextureAtlas::testFit(int x, int y, int width, int height){

    int atlasTilesX = this->width / TEXTURE_TILE_SIZE;
    int atlasTilesY = this->height / TEXTURE_TILE_SIZE;

    // test if texture would be able to fit into the atlas if it was empty
    if(x + width > atlasTilesX || y + height > atlasTilesY){
        // Texture would go out of bounds
        printf("Texture would go out of bounds\n");
        return -1;
    }

    // texture might fit, testing if all needed tiles are free
    for(int tileX = x; tileX < x + width; tileX++){
        for(int tileY = y; tileY < y + height; tileY++){
            int addr = (y * atlasTilesX) + x;   // number of the Tile in the atlas array
            if(*(tiles + (sizeof(TextureTile*) * addr)) != nullptr){
                printf("Tile %d %d already in use, texture won't fit here\n",tileX,tileY);
                return -1;
            }
        }
    }

    return 0;
}

void GLTextureAtlas::placeTexture(Texture* texture, const char* key){
    int xTiles =  texture->width/TEXTURE_TILE_SIZE;
    if(texture->width % TEXTURE_TILE_SIZE){
        // texture doesn't align with tiles on X, and since the fractional part gets cut off at the division, the width has to be incremented
        xTiles++;
    }
    int yTiles = texture->height/TEXTURE_TILE_SIZE;
    if(texture->height % TEXTURE_TILE_SIZE){
        yTiles++;
    }
    
    int atlasTilesX = width / TEXTURE_TILE_SIZE;
    int atlasTilesY = height / TEXTURE_TILE_SIZE;
    printf("Texture needs %d Tiles in X and %d Tiles in Y direction, Atlas size is %dx%d\n", xTiles,yTiles,atlasTilesX,atlasTilesY);
    int x, y;
    bool fits = false;
    for(y = 0; y < atlasTilesY - yTiles; y++){
        for(x = 0; x < atlasTilesX - xTiles; x++){
            if(testFit(x,y,xTiles,yTiles) == 0){
                printf("Texture fits at Tile %d %d (normalised to %f %f)\n",x,y,(float)x / atlasTilesX,(float)y / atlasTilesY);
                fits = true;
                break;
            }
        }
        if(fits){
            break;
        }
    }
    if(!fits){
        printf("Couldn't place Texture of size %dx%d. Try increasing the atlas size or decreasing the texture size. Splitting it up may help fitting it too.\n",texture->width,texture->height);
        return;
    }

    // Found Place to fit the Texture, adding it to the atlas. Assuming the arrays have the proper sizes
    printf("placed texture, filling atlas\n");
    for(int ytile = 0; ytile < yTiles; ytile++){
        for(int xtile = 0; xtile < xTiles; xtile++){
            int src = ytile * xTiles + xtile;   // index of the Tile in the source array (texture)
            int dst = (y + ytile) * atlasTilesX + x + xtile; // index of the Tile in the destination array (atlas)
            tiles[dst] = &texture->tiles[src];
            printf("filling tile %d %d\n",xtile,ytile);
        }
    }
    printf("filled atlas\n");
    texture->atlas = (TextureAtlas*)this;   // point back to this atlas to later retrieve the 
    map[key] = texture;
}

void GLTextureAtlas::uploadAtlas(){
    // consolidate data from tiles into one buffer
    void* data = malloc(width*height*bytesPerPixel);    // Get a buffer of the required size
    int atlasTilesX = width / TEXTURE_TILE_SIZE;
    int atlasTilesY = height / TEXTURE_TILE_SIZE;
    for(int y = 0; y < atlasTilesY; y++){
        for(int x = 0; x < atlasTilesX; x++){
            int index = y * atlasTilesX + x;
            if(tiles[index] == nullptr){
                // tile is not used, filling with 0
                for(int posY = 0; posY < TEXTURE_TILE_SIZE; posY++){
                    // only iterating down the rows, no need to go over columns
                    int addr = (y * TEXTURE_TILE_SIZE + posY) * width + x * TEXTURE_TILE_SIZE;
                    memset(data + addr,255,TEXTURE_TILE_SIZE); 
                }
            } else {
                for(int posY = 0; posY < TEXTURE_TILE_SIZE; posY++){
                    // only iterating down the rows, no need to go over columns
                    int addr = (y * TEXTURE_TILE_SIZE + posY) * width + x * TEXTURE_TILE_SIZE;
                    memcpy(data + addr,tiles[index]->data + (posY * TEXTURE_TILE_SIZE),TEXTURE_TILE_SIZE);
                }
            }
        }
    }

    // created buffer, uploading it to the GPU
    //glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D,ID);
    if(format == Texture::formats::TEXTURE_RGBA){
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
    }
    free(data);
    valid = true;
}
