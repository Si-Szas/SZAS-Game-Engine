#pragma once
#include "Window.h"

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

