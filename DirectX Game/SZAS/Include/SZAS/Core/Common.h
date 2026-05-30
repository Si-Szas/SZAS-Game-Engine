#pragma once
#include <SZAS/Core/Core.h>
#include <SZAS/Core/Logger.h>
#include <SZAS/Math/Rect.h>

namespace szas 
{
	//Groups all dependencies used by Base Class
	struct BaseDescriptor
	{
		Logger& logger;
	};

	struct WindowDescriptor
	{
		BaseDescriptor base;
		Rect size{};
	};

	struct DisplayDescriptor
	{
		WindowDescriptor window;
		GraphicsDevice& graphicsDevice;
	};

	struct GraphicsEngineDescriptor 
	{
		BaseDescriptor base;
	};

	struct GraphicsDeviceDescriptor
	{
		BaseDescriptor base;
	};

	struct SwapChainDescriptor
	{
		void* windowHandle{};
		Rect windowSize{};
	};

	enum class ShaderType 
	{
		VertexShader = 0,
		PixelShader
	};

	struct ShaderCompileDescriptor
	{
		//Instead of using a string, we use const char to make it ABI safe
		//ABI is application binary interface, a structure is ABI safe if it has same memory layout and size across all major compilers
		const char* shaderSourceName{};	//Source name of the shader
		const void* shaderSourceCode{}; //Point to actual source code of shader
		size_t shaderSourceCodeSize{};  //Size of the source code in bytes (use size_t) since it can be large
		const char* shaderEntryPoint{};	//Entry point of the shader, which is a string
		ShaderType shaderType{};		//Type of shader we are compiling
	};

	struct VertexShaderSignatureDescriptor
	{
		const ShaderBinaryPtr& vertexShaderBinary;
	};

	struct GraphicsPipelineStateDescriptor
	{
		const VertexShaderSignature& vertexShader;
		const ShaderBinary& pixelShader;
	};

	struct BinaryData
	{
		const void* data{};
		size_t dataSize{};
	};

	struct VertexBufferDescriptor
	{
		const void* vertexList{};	//Vertex list
		ui32 vertexListSize{};		//Size in bytes of the vertex list
		ui32 vertexSize;			//Holds size in bytes of a single vertex
	};

	struct ConstantBufferDescriptor
	{
		const void* buffer{};		//Since we have yet to define what constants we want to pass, make a const void*
		ui32 bufferSize{};			//Size of the buffer
	};

	struct GameDescriptor
	{
		Rect windowSize{ 1280, 720 };
		Logger::LogLevel logLevel = Logger::LogLevel::Error;
	};
}