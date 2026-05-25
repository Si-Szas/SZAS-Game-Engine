#include <SZAS/Graphics/ShaderBinary.h>
#include <SZAS/Graphics/GraphicsUtility.h>
#include <d3dcompiler.h>

szas::ShaderBinary::ShaderBinary(const ShaderCompileDescriptor& shaderCompileDescriptor, const GraphicsResourceDescriptor& graphicsResourceDescriptor) :
	GraphicsResource(graphicsResourceDescriptor), m_type(shaderCompileDescriptor.shaderType)
{
	//We don't want our attributes to be null.
	if (!shaderCompileDescriptor.shaderSourceCode) SZASLogThrowInvalidArgument("No Shader Source Code provided.");
	if (!shaderCompileDescriptor.shaderSourceCodeSize) SZASLogThrowInvalidArgument("No Shader Source Code Size provided.");
	if (!shaderCompileDescriptor.shaderSourceName) SZASLogThrowInvalidArgument("No Shader Source Name provided.");
	if (!shaderCompileDescriptor.shaderEntryPoint) SZASLogThrowInvalidArgument("No Shader Entry Point provided.");
	
	//Define flags
	UINT compileFlags{};

	//If build on debug mode, use debug flag
	#ifdef _DEBUG
		compileFlags |= D3DCOMPILE_DEBUG;
	#endif
	
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;

	//Compile HLSL source code into GPU executable bytecode
	//We cannot use SZASGraphicsLogThrowOnFail since we also want to print errors returned by the D3DCompile function
	SZASGraphicsCheckShaderCompile(D3DCompile
	(
		shaderCompileDescriptor.shaderSourceCode,		//Pointer to the source code of the shader (raw string)
		shaderCompileDescriptor.shaderSourceCodeSize,	//Size in bytes
		shaderCompileDescriptor.shaderSourceName,		//Name of the Source Files
		nullptr,										//Optional list of macro definition (pre-processor)
		nullptr,										//Interface used for handling include directives in shader source
		shaderCompileDescriptor.shaderEntryPoint,		//Name of function that acts as entry point for the shader
		szas::GraphicsUtility::GetShaderModelTarget(	//Shader model target. String that tells compiler what type of shader we are opening and the GPU feature we want to support
			shaderCompileDescriptor.shaderType
		),
		compileFlags,									//Flags 1: use to pass shader compilation options
		0,												//Flags 2: Effects-specific classes for shader effect files (FX files)
		&m_blob,										//D3DBlob allows us to retrieve compiled shader through this data type (used to store compiled data)
		&errorBlob										//Retrieve any error messages during compilation
	), errorBlob.Get(), "D3DCompile() failed.");

}

szas::BinaryData szas::ShaderBinary::GetData() const noexcept
{
	return
	{
		m_blob->GetBufferPointer(),
		m_blob->GetBufferSize()
	};
}

szas::ShaderType szas::ShaderBinary::GetShaderType() const noexcept
{
	return m_type;
}
