#pragma once
#include <Windows.h>

class Window
{
	public:
		//CONSTRUCTOR
		Window();

		//FUNCTIONS
		  //Initializes Window
		bool init();
		  //Broadcast Window Events
		bool broadcast();
		  //Checks if Window is currently running
		bool isRun();
		  //Destroys Window
		bool release();

		//EVENTS
		virtual void onCreate();
		virtual void onUpdate();
		virtual void onDestroy();

		//DECONSTRUCTOR
		~Window();

	protected:
		HWND m_hWnd;
		bool m_isRunning;
};

