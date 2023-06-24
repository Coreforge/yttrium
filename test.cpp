#include "world/World.h"
#include "world/Region.h"
#include "renderer/RendererInterface.h"
#include "test.h"
#include "Window/WindowInput.h"
#include <glm/vec4.hpp>
#include <glm/glm.hpp>
#include "GLRenderer/GLShaderSetup.h"
#include <glm/gtc/matrix_transform.hpp>
#include "renderer/Texture/Texture.h"

#include "MFLoader/MFLoader.h"

using namespace ytr;

extern World world;
extern RendererInterface* renderer;

float speed = 0.5f;
float rotationspeed = 0.1f;

void moveCamera(Camera* camera,glm::vec4 offset){
    glm::mat4 mat(1.0f);
    // rotation matrix to convert the offset vector into world space (also defines on which axis the camera can be moved)
    mat = glm::rotate(mat,glm::radians(camera->rotation.y),glm::vec3(0.0,1.0,0.0));
    // apply rotation matrix to get the offset for the camera
    offset = mat * offset;
    // add the offset to the current position
    camera->position += offset;
}

void wCallback(double delta,void* data){
    World* wld = (World*)data;
    // how the camera is supposed to move relative to the camera
    glm::vec4 mov(0.0,0.0,-delta*speed,0.0);
    moveCamera(&wld->camera,mov);
    printf("position: {%f,%f,%f}\n",wld->camera.position.x,wld->camera.position.y,wld->camera.position.z);
}

void aCallback(double delta,void* data){
    World* wld = (World*)data;
    glm::vec4 mov(-delta*speed,0.0,0.0,0.0);
    moveCamera(&wld->camera,mov);
    printf("position: {%f,%f,%f}\n",wld->camera.position.x,wld->camera.position.y,wld->camera.position.z);
}

void sCallback(double delta,void* data){
    World* wld = (World*)data;
    glm::vec4 mov(0.0,0.0,delta*speed,0.0);
    moveCamera(&wld->camera,mov);
    printf("position: {%f,%f,%f}\n",wld->camera.position.x,wld->camera.position.y,wld->camera.position.z);
}

void dCallback(double delta,void* data){
    World* wld = (World*)data;
    glm::vec4 mov(delta*speed,0.0,0.0,0.0);
    moveCamera(&wld->camera,mov);
    printf("position: {%f,%f,%f}\n",wld->camera.position.x,wld->camera.position.y,wld->camera.position.z);
}

void xCallback(double x, double delta, void* data){
    // Screen X (width) modifies world Y (side to side)
    World* world = (World*)data;
    world->camera.rotation.y = world->camera.rotation.y + (-x * rotationspeed);
    printf("camera rotation: {%f,%f,%f}\n",world->camera.rotation.x,world->camera.rotation.y,world->camera.rotation.z);
}

void yCallback(double y, double delta, void* data){
    // Screen Y (height) modifies world X (up and down)
    World* world = (World*)data;

    //glm::mat4 mat(1.0f);
    //mat = glm::rotate(mat,(float)glm::radians(-y * rotationspeed),glm::vec3(0.0,1.0,0.0));
    //world->camera.rotation = mat * world->camera.rotation;
    world->camera.rotation.x = world->camera.rotation.x + (-y * rotationspeed);
    if(world->camera.rotation.x > 90.0){
        world->camera.rotation.x = 90.0;
    }
    if(world->camera.rotation.x < -90.0){
        world->camera.rotation.x = -90.0;
    }
    
    printf("camera rotation: {%f,%f,%f} y: %f\n",world->camera.rotation.x,world->camera.rotation.y,world->camera.rotation.z,y);
}

//                   x   y   z     u   v     u   v     x   y    z
float cubeMesh[] = {0.0,0.0,0.5,  0.0,0.0,  0.0,0.0,  0.0,0.0,-1.0,
                    1.0,0.0,0.0,  1.0,0.0,  0.0,0.0,  0.0,0.0,-1.0,
                    1.0,1.0,0.0,  1.0,1.0,  0.0,0.0,  0.0,0.0,-1.0,
                    
                    0.0,0.0,0.0,  0.0,0.0,  0.0,0.0,  0.0,0.0,-1.0,
                    0.0,1.0,0.0,  0.0,1.0,  0.0,0.0,  0.0,0.0,-1.0,
                    1.0,1.0,0.0,  1.0,1.0,  0.0,0.0,  0.0,0.0,-1.0};       // bottom face

unsigned int cubeIndicies[] = {0,1,2,
                               0,1,4,
                               1,2,3,
                               2,3,4,
                               0,2,4};

const char vtxSrc[] = "#version 330 core\n"
                      "layout (location=0) in vec3 pos;\n"
                      "uniform mat4 transmat;\n"
                      "uniform vec3 col;\n"
                      "out vec3 unicolor;\n"
                      "out vec2 texcoords;\n"
                      "layout (location=1) in vec2 albcoords;\n"
                      "void main(){\n"
                      "gl_Position = transmat * vec4(pos,1.0);\n"
                      "unicolor = vec3((transmat * vec4(0.0,0.0,0.0,1.0)).xyz);\n"
                      "unicolor = col;\n"
                      "texcoords = albcoords;\n"
                      "}\n";

const char frgSrc[] = "#version 330 core\n"
                      "out vec4 color;\n"
                      "in vec3 unicolor;\n"
                      "in vec2 texcoords;\n"
                      "uniform sampler2D albedoSampler;\n"
                      "void main(){\n"
                      //"color=vec4(texcoords.rg,0.5,1.0);\n"
                      //"color = vec4(1.0,1.0,1.0,1.0);"
                      "color = texture(albedoSampler,texcoords);\n"
                      "color = vec4(color.rg,gl_FragCoord.z,color.a);\n"
                      "}\n";


void testWorld::setupLogic(RendererInterface* renderer, World* world){
    // test MFLoader
    MFLoader loader;
    loader.loadManifest("../assets/resources.mf");


    // setup references for later
    this->renderer = renderer;
    this->world = world;

    // setup test region
    Region* region = new Region;
    region->key = "region1";
    // create test object
    worldObject* testcube = new worldObject;
    // setup mesh
    Mesh* cubemesh = new Mesh;
    cubemesh->vertexData = (void*)cubeMesh;
    cubemesh->faceIndicies = cubeIndicies;
    cubemesh->nFaces = 5;
    cubemesh->setupShader = &setupDefaultShader;
    struct data{
        World* world;
        RendererInterface* renderer;
    };
    data* datastr = new data;
    datastr->world = world;
    datastr->renderer = renderer;
    cubemesh->data = datastr;
    testcube->meshes.emplace_back(cubemesh);
    testcube->position = glm::vec4(0.0,0.0,0.0,0.0);
    testcube->rotation = glm::vec4(0.0,0.0,0.0,1.0);
    testcube->scale = glm::vec4(1.0,1.0,1.0,0.0);
    cubemesh->size = sizeof(cubeMesh);
    cubemesh->nIndicies = 6;
    // add test object
    region->objects.emplace_back(testcube);
    world->regions.emplace_back(region);

    // setup Texture
    Texture* testTexture = new Texture;
    testTexture->height = 1;
    testTexture->width = 1;
    testTexture->tiles.emplace_back();
    testTexture->tiles[0].data = malloc(32*32);
    //renderer->textureManager->atlas[0]->placeTexture(testTexture,"test");
    //renderer->textureManager->atlas[0]->valid = false;
    renderer->textureManager->addTexture("testTexture",TEXTURE_TYPE_ALBEDO,testTexture);
    printf("placed texture\n");
    // setup shader
    renderer->shaderManager->addShader("testShader",vtxSrc,frgSrc);
    cubemesh->shader = renderer->shaderManager->getShader("testShader");


    //setup Camera
    world->camera.settings = &renderer->window->settings;
    world->camera.fov = 60;
    world->camera.nearClip = 0.01;
    world->camera.farClip = 1000.0;
    world->camera.setupMatrices();

    // setup inputs
    renderer->window->registerInput(&wCallback,INPUT_KEY_W,INPUT_KEY_REPEAT,this->world);
    renderer->window->registerInput(&aCallback,INPUT_KEY_A,INPUT_KEY_REPEAT,this->world);
    renderer->window->registerInput(&sCallback,INPUT_KEY_S,INPUT_KEY_REPEAT,this->world);
    renderer->window->registerInput(&dCallback,INPUT_KEY_D,INPUT_KEY_REPEAT,this->world);
    renderer->window->registerAnalogInput(&xCallback,INPUT_MOUSE_X,this->world);
    renderer->window->registerAnalogInput(&yCallback,INPUT_MOUSE_Y,this->world);
}

void testWorld::loop(double deltaTime){
    //printf("FPS: %f\n",1/deltaTime);
}
