#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

using namespace ytr;

void Camera::setupMatrices(){
    projection = glm::perspective(glm::radians(fov),aspect,(float)nearClip,(float)farClip);
    transform.position = glm::vec4(0.0,0.0,0.0,1.0);
    transform.rotation = glm::vec3(0.0,0.0,0.0);
}

/*
 * Y Points up
 * 		Y
 * 		|
 * 		|
 * 		|
 * 		|__________ Z
 * 	   /
 * 	  /
 *   X
 */

void Camera::updateRenderMatrix(){
	glm::vec3 forward;
	forward.x = cos(glm::radians(transform.rotation.y));
	forward.z = sin(glm::radians(transform.rotation.y));
	forward.y = sin(glm::radians(transform.rotation.x));
	forward = glm::normalize(forward);
	glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0.0,1.0,0.0),forward));
	glm::vec3 up = glm::cross(forward, right);

	//glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0.0,1.0,0.0),glm::vec3(transform.rotation)));

    glm::mat4 rot(1.0f);
    rot = glm::rotate(rot,glm::radians(transform.rotation.x),glm::vec3(1.0,0.0,0.0));
    rot = glm::rotate(rot,glm::radians(transform.rotation.y),glm::vec3(0.0,1.0,0.0));
    rot = glm::rotate(rot,glm::radians(transform.rotation.z),glm::vec3(0.0,0.0,1.0));
    glm::vec4 cent = glm::vec4(1.0,0.0,0.0,0.0);// * (glm::translate(m, v) * rot);
    //rot = glm::translate(rot, transform.position);
    cent = cent * rot;


    glm::mat4 mov(1.0f);
    mov = glm::translate(mov,glm::vec3(transform.position));
    glm::mat4 offsetMat(1.0f);
    offsetMat = glm::translate(offsetMat,glm::vec3(offset));
    glm::mat4 mat(1.0f);
    //mat = offsetMat * rot;
    mat = rot * mov;
    //mat = projection * mat;
    //mat = glm::lookAt(transform.position, transform.position + glm::vec3(cent.x,cent.y,cent.z),up);
    renderMatrix = mat;
}
