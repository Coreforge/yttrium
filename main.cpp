
#include "Window/Window.h"
#include "GLRenderer/GLWindow.h"
#include "renderer/RendererInterface.h"
#include "world/World.h"
#include "GLRenderer/GLRenderer.h"
#include "renderer/Texture/TextureManager.h"

#include "test.h"


#include <chrono>

using namespace ytr;

RendererInterface* renderer;
World world;
GameLogic* logic;

int main(){

    // use only GL for now
    renderer = (RendererInterface*)new GLRenderer;
    renderer->window = (renderWindow*)new GLWindow;
    //Window = (renderWindow*) new GLWindow;
    windowSettings settings;
    settings.height = 1080;
    settings.width = 1920;
    settings.major = 3;
    settings.minor = 3;
    settings.windowType = WINDOWED;
    settings.AALevel = 8;
    renderer->window->createWindow(settings);
    renderer->window->cursorRawMotion();
    renderer->initBuffers();
    renderer->window->setupInput();
    
    std::chrono::high_resolution_clock::time_point timeStart,timeStop;

    // setting up logic after setting up the engine
    logic = (GameLogic*)new testWorld;
    logic->setupLogic(renderer,&world);
    double deltaMicros;
    double delta;
    while(1){
        timeStart = timeStop;
        timeStop = std::chrono::high_resolution_clock::now();
        renderer->renderFrame();
        renderer->window->inputLoop(delta);
        
        deltaMicros = std::chrono::duration_cast<std::chrono::microseconds>(timeStop-timeStart).count();
        delta = deltaMicros/1000000.0f;
        logic->loop(delta);
    }
    return 0;
}
