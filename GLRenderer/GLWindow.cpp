#include "GLWindow.h"
#include "../renderer/RendererInterface.h"
#include <cstdio>

using namespace ytr;

GLWindow::GLWindow(){
    
}

int glfwKeyToEnum(int key){
    // this could be done better with an array, but that's more work for now. maybe later
    switch(key){
        case GLFW_KEY_W:
            return INPUT_KEY_W;
        case GLFW_KEY_A:
            return INPUT_KEY_A;
        case GLFW_KEY_S:
            return INPUT_KEY_S;
        case GLFW_KEY_D:
            return INPUT_KEY_D;
        case GLFW_KEY_SPACE:
        	return INPUT_KEY_SPACE;
        case GLFW_KEY_LEFT_SHIFT:
        	return INPUT_KEY_LSHIFT;
    }
    return -1;
}

int glfwButtonToEnum(int button){
	switch(button){
	case GLFW_MOUSE_BUTTON_LEFT:
		return INPUT_KEY_MOUSE_LEFT;
	case GLFW_MOUSE_BUTTON_RIGHT:
		return INPUT_KEY_MOUSE_RIGHT;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		return INPUT_KEY_MOUSE_MIDDLE;
	}
	return -1;
}

void keyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods){

	GLWindow* thisWindow = (GLWindow*)glfwGetWindowUserPointer(window);
    int localKey = glfwKeyToEnum(key);
    if(localKey != -1){
        // valid key
        if(action == GLFW_PRESS){
            // set key to pressed in status array
            (thisWindow)->keyStatus[localKey] = true;
        }
        if(action == GLFW_RELEASE){
            // set key to not pressed in status array
            (thisWindow)->keyStatus[localKey] = false;
        }

        for(int i = 0; i < (thisWindow)->keyCallbacks[localKey].size(); i++){
            if((thisWindow)->keyCallbacks[localKey][i].callback != nullptr){
                switch((thisWindow)->keyCallbacks[localKey][i].type){
                    case INPUT_KEY_PRESS:
                        if(action == GLFW_PRESS){
                        	thisWindow->keyCallbacks[localKey][i].callback(thisWindow->delta,thisWindow->keyCallbacks[localKey][i].data);
                        }
                        break;
                    case INPUT_KEY_REPEAT:
                        if(action != GLFW_RELEASE){
                            // key either was pressed or repeated, doesn't really matter. Repeat has to be true anyways
                        	thisWindow->keyCallbacks[localKey][i].repeat = true;
                        }
                        if(action == GLFW_RELEASE){
                            // key was released, stop repeating it
                        	thisWindow->keyCallbacks[localKey][i].repeat = false;
                        }
                        break;
                    case INPUT_KEY_RELEASE:
                        if(action == GLFW_RELEASE){
                        	thisWindow->keyCallbacks[localKey][i].callback(thisWindow->delta,thisWindow->keyCallbacks[localKey][i].data);
                        }
                        break;
                }
                
            }
        }
    }
}

void mouseButtonInputCallback(GLFWwindow* window, int button, int action, int mods){
	GLWindow* thisWindow = (GLWindow*)glfwGetWindowUserPointer(window);
	int localButton = glfwButtonToEnum(button);
	if(localButton != -1){
        // valid key
        if(action == GLFW_PRESS){
            // set key to pressed in status array
            (thisWindow)->keyStatus[localButton] = true;
        }
        if(action == GLFW_RELEASE){
            // set key to not pressed in status array
            (thisWindow)->keyStatus[localButton] = false;
        }

        for(int i = 0; i < (thisWindow)->keyCallbacks[localButton].size(); i++){
            if((thisWindow)->keyCallbacks[localButton][i].callback != nullptr){
                switch((thisWindow)->keyCallbacks[localButton][i].type){
                    case INPUT_KEY_PRESS:
                        if(action == GLFW_PRESS){
                        	thisWindow->keyCallbacks[localButton][i].callback(thisWindow->delta,thisWindow->keyCallbacks[localButton][i].data);
                        }
                        break;
                    case INPUT_KEY_REPEAT:
                        if(action != GLFW_RELEASE){
                            // key either was pressed or repeated, doesn't really matter. Repeat has to be true anyways
                        	thisWindow->keyCallbacks[localButton][i].repeat = true;
                        }
                        if(action == GLFW_RELEASE){
                            // key was released, stop repeating it
                        	thisWindow->keyCallbacks[localButton][i].repeat = false;
                        }
                        break;
                    case INPUT_KEY_RELEASE:
                        if(action == GLFW_RELEASE){
                        	thisWindow->keyCallbacks[localButton][i].callback(thisWindow->delta,thisWindow->keyCallbacks[localButton][i].data);
                        }
                        break;
                }

            }
        }
	}
}

bool GLWindow::getKeyStatus(int key){
	return keyStatus[key];
}

void GLWindow::inputLoop(double deltaTime){
    for(int i = 0; i < INPUT_KEYS_COUNT; i++){
        for(int c = 0; c < keyCallbacks[i].size(); c++){
            if(keyCallbacks[i][c].type == INPUT_KEY_REPEAT && keyCallbacks[i][c].repeat && keyCallbacks[i][c].callback != nullptr){
                keyCallbacks[i][c].callback(deltaTime,keyCallbacks[i][c].data);
            }
        }
    }
    double xpos;
    double ypos;
    glfwGetCursorPos(glfwWindow,&xpos,&ypos);
    double deltaX = xpos - lastxpos;
    double deltaY = ypos - lastypos;
    lastxpos = xpos;
    lastypos = ypos;
    for(int i = 0; i < INPUT_ANALOG_COUNT; i++){
        for(int c = 0; c < AnalogCallbacks[i].size(); c++){
            if(deltaX != 0.0 && i == INPUT_MOUSE_X && AnalogCallbacks[i][c].callback != nullptr){
                AnalogCallbacks[i][c].callback(deltaX,deltaTime,AnalogCallbacks[i][c].data);
            }
            if(deltaY != 0.0 && i == INPUT_MOUSE_Y && AnalogCallbacks[i][c].callback != nullptr){
                AnalogCallbacks[i][c].callback(deltaY,deltaTime,AnalogCallbacks[i][c].data);
            }
        }
    }
    //printf("X: %f Y: %f\n",deltaX,deltaY);
}

int GLWindow::createWindow(windowSettings settings){
    if(!glfwInit()){
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,settings.major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,settings.minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES,settings.AALevel);

    glfwWindow = glfwCreateWindow(settings.width,settings.height,"",NULL,NULL);
    if(!glfwWindow){
        return -1;
    }
    glfwMakeContextCurrent(glfwWindow);
    glViewport(0,0,settings.width,settings.height);
    glewInit();
    glEnable(GL_MULTISAMPLE);
    this->settings = settings;
    glfwSetWindowUserPointer(glfwWindow,this);
    return 0;
}

void GLWindow::cursorLockedHiddenCursor(){
    glfwSetInputMode(glfwWindow,GLFW_CURSOR,GLFW_CURSOR_HIDDEN);
    glfwSetInputMode(glfwWindow,GLFW_RAW_MOUSE_MOTION,GLFW_FALSE);
}

void GLWindow::cursorNormal(){
    glfwSetInputMode(glfwWindow,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
    glfwSetInputMode(glfwWindow,GLFW_RAW_MOUSE_MOTION,GLFW_FALSE);
}

void GLWindow::cursorRawMotion(){
    if(glfwRawMouseMotionSupported()){
        glfwSetInputMode(glfwWindow,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
        glfwSetInputMode(glfwWindow,GLFW_RAW_MOUSE_MOTION,GLFW_TRUE);
    }
}

void GLWindow::setupInput(){
    glfwSetKeyCallback(glfwWindow,(GLFWkeyfun)&keyInputCallback);
    glfwSetMouseButtonCallback(glfwWindow, &mouseButtonInputCallback);

    double xpos;
    double ypos;
    glfwGetCursorPos(glfwWindow,&xpos,&ypos);
    lastxpos = xpos;
    lastypos = ypos;
}

int GLWindow::registerAnalogInput(void callback(double,double,void*), int axis, void* data){
    AnalogCallbacks[axis].emplace_back(GLinputAnalogCallback{callback,axis,data});
    return 0;
}

int  GLWindow::registerInput(void callback(double,void*), int key, int action, void* data){
    keyCallbacks[key].emplace_back(GLinputCallback{callback,action,false,data});
    return 0;
}

void GLWindow::update(){
	//glfwMakeContextCurrent(glfwWindow);
	glfwSwapBuffers(glfwWindow);
	glfwPollEvents();
}

int GLWindow::registerCloseCallback(void callback(void*), void* data){
	closeCallbacks.emplace_back(GLCloseCallback{callback, data});
	return 0;
}

void GLWindow::detachContext(){
	glfwMakeContextCurrent(nullptr);
}

void GLWindow::useContext(){
	glfwMakeContextCurrent(glfwWindow);
}



