#pragma once
#include <stdexcept>
#include <memory>

#define szas_disable_copy_and_move(Class)\
protected:\
	Class(const Class&) = delete;\
	Class& operator=(const Class&) = delete;\
	Class(Class&&) = delete;\
	Class& operator=(Class&&) = delete;

namespace szas {
	///////////// WINDOW /////////////
	class Base;
	class Window;
	class Display;
	class Game;
	//Logger
	class Logger;

	///////////// RENDERER /////////////
	//Graphics Engine
	class GraphicsEngine;
	class GraphicsDevice;
	class SwapChain;
	class DeviceContext;
	class GraphicsPipelineState;
		//Shaders
	class ShaderBinary;
	class VertexShaderSignature;
		//Buffers
	class VertexBuffer;
	class ConstantBuffer;
	class IndexBuffer;
	
	///////////// WORLD /////////////
	//World
	class World;
	class WorldRenderer;
	//Game Object
	class AGameObject;
	//Components
	class AComponent;
		//Transform Component
	class TransformComponent;
	

	/////////// GAME LOOP - ENGINE TIME ///////////
	class EngineTime;

	//Type Aliases
	using i32 = int;
	using ui32 = unsigned int;
	using f32 = float;
	using d64 = double;
	
	template <typename Type> using RefPtr = std::shared_ptr<Type>;
	template <typename Type> using UniquePtr = std::unique_ptr<Type>;
}