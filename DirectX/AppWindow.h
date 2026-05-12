#pragma once
#include "Window.h"
#include "GraphicsEngine.h"

class AppWindow: public Window
{
	public:
		//CONSTRUCTOR 
		AppWindow();

		// Inherited via Window
		void onCreate() override;
		void onUpdate() override;
		void onDestroy() override;

		//DECONSTRUCTOR
		~AppWindow();
};

