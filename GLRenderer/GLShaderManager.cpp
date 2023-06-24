#include "GLShaderManager.h"
#include "../renderer/Shader.h"
#include "GLIncludes.h"
#include <cstdio>

using namespace ytr;

void compile(GLuint id, const char* source){
    glShaderSource(id,1,&source,NULL);
    glCompileShader(id);
}

int GLShaderManager::addShader(const char* key,const char* vertex, const char* fragment){
    Shader* shader = new Shader;
    GLuint vid = glCreateShader(GL_VERTEX_SHADER);
    compile(vid,vertex);
    int success;
    glGetShaderiv(vid,GL_COMPILE_STATUS,&success);
    if(!success){
        char error[1024];
        glGetShaderInfoLog(vid,1024,NULL,error);
        printf("Vertex Shader compile error: %s\n",error);
        glDeleteShader(vid);
        return -1;
    }

    GLuint fid = glCreateShader(GL_FRAGMENT_SHADER);
    compile(fid,fragment);
    glGetShaderiv(fid,GL_COMPILE_STATUS,&success);
    if(!success){
        char error[1024];
        glGetShaderInfoLog(fid,1024,NULL,error);
        printf("Fragment Shader compile error: %s\n",error);
        glDeleteShader(vid);
        glDeleteShader(fid);
        return -1;
    }

    shader->id = glCreateProgram();
    glAttachShader(shader->id,vid);
    glAttachShader(shader->id,fid);
    glLinkProgram(shader->id);
    glGetProgramiv(shader->id,GL_LINK_STATUS,&success);

    if(!success){
        char error[1024];
        glGetProgramInfoLog(shader->id,1024,NULL,error);
        printf("Link error: %s\n",error);
        glDeleteShader(vid);
        glDeleteShader(fid);
        glDeleteProgram((shader->id));
        return -1;
    }
    shaders[key] = shader;
    glDeleteShader(vid);
    glDeleteShader(fid);
    return 0;
}

GLuint GLShaderManager::createShaderProgram(const char* vertex, const char* fragment){
	GLuint shaderID;
	GLuint vid = glCreateShader(GL_VERTEX_SHADER);
	    compile(vid,vertex);
	    int success;
	    glGetShaderiv(vid,GL_COMPILE_STATUS,&success);
	    if(!success){
	        char error[1024];
	        glGetShaderInfoLog(vid,1024,NULL,error);
	        printf("Vertex Shader compile error: %s\n",error);
	        glDeleteShader(vid);
	        return -1;
	    }

	    GLuint fid = glCreateShader(GL_FRAGMENT_SHADER);
	    compile(fid,fragment);
	    glGetShaderiv(fid,GL_COMPILE_STATUS,&success);
	    if(!success){
	        char error[1024];
	        glGetShaderInfoLog(fid,1024,NULL,error);
	        printf("Fragment Shader compile error: %s\n",error);
	        glDeleteShader(vid);
	        glDeleteShader(fid);
	        return -1;
	    }

	    shaderID = glCreateProgram();
	    glAttachShader(shaderID,vid);
	    glAttachShader(shaderID,fid);
	    glLinkProgram(shaderID);
	    glGetProgramiv(shaderID,GL_LINK_STATUS,&success);

	    if(!success){
	        char error[1024];
	        glGetProgramInfoLog(shaderID,1024,NULL,error);
	        printf("Link error: %s\n",error);
	        glDeleteShader(vid);
	        glDeleteShader(fid);
	        glDeleteProgram((shaderID));
	        return -1;
	    }
	    glDeleteShader(vid);
	    glDeleteShader(fid);
	return shaderID;
}

Shader* GLShaderManager::getShader(const char* key){
    return shaders.at(key);
}
