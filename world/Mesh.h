#pragma once
//#include "worldObject.h"
#include "../renderer/Shader.h"

namespace ytr{

	class worldObject;

	class Mesh{
		public:
			void* vertexData;
			Shader* shader;
			void (*setupShader)(worldObject*, void*, unsigned int);  // pointer to a function that sets up the shader programm for drawing (setting uniforms). Gets called right before drawing, so there shouldn't be any expensive operations in there ideally
			unsigned int size;	// size of vertex data array
			unsigned int nVerts;	// number of vertices in Mesh
			unsigned int nFaces;	// number of faces in Mesh
			unsigned int nIndicies;	// number of vertices to be drawn. unused
			unsigned int* faceIndicies;	// indicies of the vertices
			void* data;
			/*

			The vertex data should be layed out in the following manner
				 ____________________________________________________________
				|                 |           |           |                 |
				|     position    |   albedo  |   normal  |      normal     |
				|                 |   coords  |   coords  |    direction    |
				|      float      |   float   |   float   |      float      |
				|_________________|___________|___________|_________________|
				|     |     |     |     |     |     |     |     |     |     |
				|  x  |  y  |  z  |  u  |  v  |  u  |  v  |  x  |  y  |  z  |
				|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|
			*/
	};
}
