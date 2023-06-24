#pragma once

#include "../Window/Window.h"
#include "GLIncludes.h"
#include "../Window/WindowInput.h"
#include <vector>

namespace ytr{

	struct GLinputCallback{
		void(*callback)(double,void*);
		int type;
		bool repeat;
		void* data;
	};

	struct GLinputAnalogCallback{
		void(*callback)(double,double,void*);
		int axis;
		void* data;
	};

	struct GLCloseCallback{
		void(*callback)(void*);
		void* data;
	};

	class GLRenderer;

	class GLWindow : public renderWindow{
		public:
		int createWindow(struct windowSettings settings) override;
		int registerInput(void callback(double,void*), int key, int action, void* data) override;
		int registerAnalogInput(void callback(double,double,void*), int axis,void* data) override;
		int registerCloseCallback(void callback(void*), void* data) override;
		bool getKeyStatus(int key) override;
		void setupInput() override;
		void inputLoop(double deltaTime) override;
		// set cursor modes
		void cursorRawMotion() override;
		void cursorLockedHiddenCursor() override;
		void cursorNormal() override;

		void detachContext();
		void useContext();

		void update() override;
		//void keyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		GLWindow();
			GLFWwindow* glfwWindow;
			std::vector<GLinputCallback> keyCallbacks[inputKeys::INPUT_KEYS_COUNT];
			std::vector<GLinputAnalogCallback> AnalogCallbacks[INPUT_ANALOG_COUNT];
			std::vector<GLCloseCallback> closeCallbacks;
			bool keyStatus[INPUT_KEYS_COUNT];

		GLRenderer* renderer;

		private:
			double lastxpos;
			double lastypos;
	};
}
