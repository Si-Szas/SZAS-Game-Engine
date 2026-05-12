#include "AppWindow.h"

AppWindow::AppWindow()
{
}

void AppWindow::onCreate()
{
	//Create Window
	Window::onCreate();
	//Create Graphics Engine
	GraphicsEngine::get()->init();
}

void AppWindow::onUpdate()
{
	//Update Window
	Window::onUpdate();
}

void AppWindow::onDestroy()
{
	//Destroy Window
	Window::onDestroy();
	//Destroy Graphics Engine
	GraphicsEngine::get()->release();
}

AppWindow::~AppWindow()
{
}