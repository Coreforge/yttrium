#pragma once

/*
 *
 * This only includes stuff that isn't specific to one renderer (even though currently only one exists, and that may never change)
 *
 */

#include "renderer/RendererInterface.h"
#include "renderer/ResourceManager.h"
#include "renderer/SimpleResourceManager.h"
#include "renderer/Resource.h"

#include "Window/Window.h"
#include "Window/WindowInput.h"
#include "GameLogic/GameLogic.h"

#include "renderer/Camera.h"
#include "world/World.h"
#include "world/WorldNode.h"
#include "world/MeshBase.h"
#include "world/MeshWorldNode.h"
