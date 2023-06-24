#pragma once
#include "GameLogic/GameLogic.h"

class testWorld : GameLogic{
    void setupLogic(RendererInterface* renderer, World* world);
    void loop(double deltaTime);
};

void setupTestWorld();