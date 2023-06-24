#include "GLShaderSetup.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../world/World.h"
#include <cstdio>
#include "../renderer/RendererInterface.h"
#include "Texture/GLTextureAtlas.h"
#include "Texture/GLTextureManager.h"

using namespace ytr;

void setupDefaultShader(worldObject* obj, void* data, unsigned int id){
    // setup trandformation matrix
    glm::mat4 mat(1.0f);

    struct dataStruct{
        World* world;
        RendererInterface* renderer;
    };

    dataStruct* datastr = (dataStruct*)data;

    World* world = datastr->world;
    RendererInterface* renderer = datastr->renderer;
    /*
    // rotate according to the camera
    glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0.0,1.0,0.0),glm::vec3(world->camera.rotation)));

    glm::mat4 rot(1.0f);
    rot = glm::rotate(rot,glm::radians(-world->camera.rotation.x),glm::vec3(1.0,0.0,0.0));
    rot = glm::rotate(rot,glm::radians(-world->camera.rotation.y),glm::vec3(0.0,1.0,0.0));
    rot = glm::rotate(rot,glm::radians(-world->camera.rotation.z),glm::vec3(0.0,0.0,1.0));
    //glm::vec4 at(0.0,0.0,-1.0,1.0);
    //at = rot * at;
    glm::mat4 mov(1.0f);
    mov = glm::translate(mov,glm::vec3(-world->camera.position));
    //at = mov * at;
    mat = rot * mov;

    // apply projection matrix
    mat = world->camera.projection * mat;
*/
    // set transformation matrix uniform in shader program
    GLint trans_loc = glGetUniformLocation(id,"transmat");
    glUniformMatrix4fv(trans_loc,1,GL_FALSE,glm::value_ptr(mat));
    trans_loc = glGetUniformLocation(id,"col");
    //glUniform3f(trans_loc,tmp2.x,tmp2.y,tmp2.z);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,((GLTextureManager*)renderer->textureManager)->albedo->ID);
    trans_loc = glGetUniformLocation(id,"albedoSampler");
    glUniform1i(trans_loc,0);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
}
