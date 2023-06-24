#include "GLRenderer.h"
#include "GLWindow.h"
#include "GLShaderManager.h"
#include "Texture/GLTextureAtlas.h"
#include "Texture/GLTextureManager.h"

#include <world/MeshWorldNode.h>

using namespace ytr;

void GLRenderer::initBuffers(){
    // create Buffer that stores mesh data during rendering. Rewriting one buffer for every mesh isn't very efficient
    glGenBuffers(1,&meshVBO);
    glGenVertexArrays(1,&meshVAO);
    glBindVertexArray(meshVAO);
    // set up vertex attributes
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,40,(void*)0);   // local position, vec3
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,40,(void*)12);  // albedo coords, vec2
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,40,(void*)20);  // normal coords, vec2
    glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE,40,(void*)28);  // normal vector, vec3

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    //glEnableVertexAttribArray(2);
    //glEnableVertexAttribArray(3);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
}

void GLRenderer::drawObject(worldObject* obj){
    for(int i = 0; i < obj->meshes.size();i++){
        //iterate over meshes
        glBindVertexArray(meshVAO);
        glBindBuffer(GL_ARRAY_BUFFER,meshVBO);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,40,(void*)0);   // local position, vec3
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,40,(void*)12);  // albedo coords, vec2
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,40,(void*)20);  // normal coords, vec2
    glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE,40,(void*)28);  // normal vector, vec3

    glEnableVertexAttribArray(0);
        glBufferData(GL_ARRAY_BUFFER,obj->meshes[i]->size,obj->meshes[i]->vertexData,GL_DYNAMIC_DRAW);
        if(obj->meshes[i]->shader){
            glUseProgram(obj->meshes[i]->shader->id);
            obj->meshes[i]->setupShader(obj,obj->meshes[i]->data,obj->meshes[i]->shader->id);
        }
        //glDrawArrays(GL_TRIANGLES,0,obj->meshes[i]->nIndicies);
        glDrawElements(GL_TRIANGLES,obj->meshes[i]->nFaces*3,GL_UNSIGNED_INT,obj->meshes[i]->faceIndicies);
    }
}

void GLRenderer::renderNode(WorldNode* node){
	for(int n = 0; n < node->children.size(); n++){
		renderNode(node->children[n]);
	}

	if(node->type == node->NODE_MESH){
		MeshWorldNode* mwn = (MeshWorldNode*)node;
		mwn->mesh->setupData();
		mwn->mesh->setupShader();
		mwn->mesh->draw(cam, mwn->transform);
	}
}

void GLRenderer::renderFrame(World* world){
    //glClearColor(0.1f,0.3f,0.7f,0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /*if(((GLTextureManager*)textureManager)->valid == false){
        ((GLTextureManager*)textureManager)->update();
    }*/
    /*for(int r = 0; r < world->nodes.size(); r++){
        // iterate over nodes
        for(int o = 0; o < world->regions[r]->objects.size(); o++){
            drawObject(world->regions[r]->objects[o]);
        }
    	renderNode(world->nodes[r]);
    }*/
    cam->updateRenderMatrix();
	renderNode(world->rootNode);
    window->update();
}

GLRenderer::GLRenderer(){
    //shaderManager = (ShaderManager*) new GLShaderManager;
    //textureManager = (TextureManager*) new GLTextureManager;
    /*textureManager->atlas.emplace_back((TextureAtlas*)new GLTextureAtlas);     // first atlas is for albedo
    textureManager->atlas[0]->initAtlas(4096,4096);
    textureManager->atlas[0]->bytesPerPixel = 4;    // RGBA
    textureManager->atlas[0]->format = Texture::formats::TEXTURE_RGBA;*/
    //((GLTextureManager*)textureManager)->init(2048);
}
