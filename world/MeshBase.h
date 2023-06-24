#pragma once

#include "../math/Transform.h"
#include "../renderer/Camera.h"

namespace ytr{
class MeshBase{
public:
	/*
	 * this function should ensure that the data for this mesh is ready for rendering
	 * LOD filtering may be done by the subclass
	 *
	 * If this mesh gets drawn multiple times, this function might be called again, but it might also not
	 * if it's drawn multiple times back to back (i.e. when rendering multiple instances or multiple perspectives)
	 *
	 * If other objects have been drawn in the mean time, this will be called again to ensure the data is up to date
	 *
	 * lod: if lod is -1 (aka not specified), the subclass can handle it however it likes to
	 */
	virtual void setupData(int lod = -1) = 0;

	/*
	 * Set up shaders ready for rendering
	 *
	 * not called again for instances or multiple perspectives if material properties didn't change
	 */
	virtual void setupShader() = 0;

	/*
	 * Draw the object once.
	 *
	 * Do this for the camera that has been passed
	 *
	 */
	virtual void draw(Camera* cam, Transform transform) = 0;

	// usually means this mesh can't be rendered, something else is done instead (or not)
	bool hasError;


	virtual ~MeshBase(){

	}
};
}
