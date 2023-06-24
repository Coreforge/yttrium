
#pragma once

namespace ytr{

	enum windowType{
		WINDOWED,
		WINDOWED_BORDERLESS,
		FULLSCREEN
	};

	struct windowSettings{
		int windowType;
		int width;
		int height;
		int major;
		int minor;
		int AALevel;
	};

	class renderWindow {
		public:
		int stuff;
		double delta;
		windowSettings settings;
		virtual int createWindow(struct windowSettings settings) = 0;
		virtual int registerInput(void callback(double,void*), int key, int action, void* data) = 0;
		virtual int registerAnalogInput(void callback(double,double,void*), int axis, void* data) = 0;
		virtual int registerCloseCallback(void callback(void*), void* data) = 0;
		virtual bool getKeyStatus(int key) = 0;
		virtual void setupInput() = 0;
		virtual void inputLoop(double deltaTime) = 0;
		// set cursor modes
		virtual void cursorRawMotion() = 0;
		virtual void cursorLockedHiddenCursor() = 0;
		virtual void cursorNormal() = 0;
		// basically swap buffers and poll events
		virtual void update() = 0;
		renderWindow();
		~renderWindow();
	};
}
