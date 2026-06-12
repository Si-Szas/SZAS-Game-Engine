#pragma once
#include <SZAS/Core/Core.h>
#include <SZAS/Core/Logger.h>
#include <SZAS/Math/Rect.h>
#include <SZAS/Math/Vec3.h>
#include <SZAS/Math/Vec4.h>

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

	struct WorldRendererDescriptor 
	{
		BaseDescriptor base;
		GraphicsDevice& graphicsEngine;
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
		PixelShader,
		HullShader,
		DomainShader
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
		const RefPtr<ShaderBinary>& vertexShaderBinary;
	};

	struct GraphicsPipelineStateDescriptor
	{
		const VertexShaderSignature& vertexShader;
		const ShaderBinary& pixelShader;
		const ShaderBinary& hullShader;
		const ShaderBinary& domainShader;
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

	struct IndexBufferDescriptor
	{
		const ui32* indexList{};	//Since the index buffer just contains the indices of objects, it is not a void*
		ui32 indexListSize{};		//Size of the buffer
	};

	//POINTS
	struct Vertex
	{
		Vec3 position;
		Vec4 color;
	};

	struct WorldDescriptor {
		BaseDescriptor base;
	};

	struct AGameObjectDescriptor
	{
		BaseDescriptor base;
		World& world;
	};

	struct AComponentDescriptor
	{
		BaseDescriptor base;
		AGameObject& object;
		World& world;
	};

	struct GameDescriptor
	{
		Rect windowSize{ 1280, 720 };
		Logger::LogLevel logLevel = Logger::LogLevel::Error;
	};
}