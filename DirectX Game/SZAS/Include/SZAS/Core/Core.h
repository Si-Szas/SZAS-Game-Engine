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
	//Window
	class Base;
	class Window;
	class Display;
	class Game;
	//Graphics Engine
	class GraphicsEngine;
	class GraphicsDevice;
	//Logger
	class Logger;
	//Swap Chain
	class SwapChain;
	//Device Context
	class DeviceContext;
	//Shader Binary
	class ShaderBinary;
	//Graphics Pipeline State
	class GraphicsPipelineState;
	//Vertex Buffer
	class VertexBuffer;
	//Vertex Shader Signature
	class VertexShaderSignature;
	//Constant Buffer
	class ConstantBuffer;
	//Engine Time
	class EngineTime;

	//Type Aliases
	using i32 = int;
	using ui32 = unsigned int;
	using f32 = float;
	using d64 = double;
	
	template <typename T> using RefPtr = std::shared_ptr<T>;
	template <typename T> using UniquePtr = std::unique_ptr<T>;
}