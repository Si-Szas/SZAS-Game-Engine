#pragma once
#include <stdexcept>
#include <memory>

namespace szas {
	//Window
	class Base;
	class Window;
	class Display;
	class Game;
	//Graphics Engine
	class GraphicsEngine;
	class RenderSystem;
	//Logger
	class Logger;
	//Swap Chain
	class SwapChain;

	//Type Aliases
	using i32 = int;
	using ui32 = unsigned int;
	using f32 = float;
	using d64 = double;
	//All resources shared by render system, and they can have multiple owners, so we can use shared pointer
	using SwapChainPtr = std::shared_ptr<SwapChain>;
}