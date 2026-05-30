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
	//All resources shared by render system, and they can have multiple owners, so we can use shared pointer
	using SwapChainPtr = std::shared_ptr<SwapChain>;
	//Alias to device context pointer
	using DeviceContextPtr = std::shared_ptr<DeviceContext>;
	//Alias so ShaderPtr
	using ShaderBinaryPtr = std::shared_ptr<ShaderBinary>;
	//Graphics Pipeline State
	using GraphicsPipelineStatePtr = std::shared_ptr<GraphicsPipelineState>;
	//Vertex Buffer Pointer
	using VertexBufferPtr = std::shared_ptr<VertexBuffer>;
	//Vertex Shader Signature Pointer
	using VertexShaderSignaturePtr = std::shared_ptr<VertexShaderSignature>;
	//Constant Buffer Pointer
	using ConstantBufferPtr = std::shared_ptr<ConstantBuffer>;
}