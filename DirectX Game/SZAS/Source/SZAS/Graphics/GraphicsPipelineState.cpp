#include <SZAS/Graphics/GraphicsPipelineState.h>
#include <SZAS/Graphics/ShaderBinary.h>

szas::GraphicsPipelineState::GraphicsPipelineState(const GraphicsPipelineStateDescriptor& graphicsPipelineStateDescriptor, const GraphicsResourceDescriptor& descriptor):
	GraphicsResource(descriptor)
{
	//Ensures that the shader type of the vertex shader is actually a vertex shader
	if (graphicsPipelineStateDescriptor.vertexShader.GetShaderType() != ShaderType::VertexShader)
		SZASLogThrowInvalidArgument("The 'vertexShader' member is not a valid vertex shader binary.");

	if (graphicsPipelineStateDescriptor.pixelShader.GetShaderType() != ShaderType::PixelShader)
		SZASLogThrowInvalidArgument("The 'pixelShader' member is not a valid pixel shader binary.");

	//Retrieve Vertex Shader Binary Data
	auto vs = graphicsPipelineStateDescriptor.vertexShader.GetShaderData();
	//Retrieve Pixel Shader Binary Data
	auto ps = graphicsPipelineStateDescriptor.pixelShader.GetShaderData();

	//Get a reference to the D3D11 Device and call its CreateVertexShader
		//This method creates a vertex shader object from bytecode (takes HLSL bytecode)
		// Returns a d3d11 vertex shader object that can be bound to gpu pipeline)
	SZASGraphicsLogThrowOnFail(
		m_d3dDevice.CreateVertexShader
		(
			vs.data,		//Shader byte code (Pointer to binary data)
			vs.dataSize,	//Size of shader byte code
			nullptr,		//Pointer to a D3D11 class linkage object. Interface used to enable polymorphism by HLSL interface & classes (dynamic implementation binding)
			&m_vertexShader	//Output parameter where created D3D11 Shader object will be stored
		),
		"CreateVertexShader() failed."
	);

	SZASGraphicsLogThrowOnFail(
		m_d3dDevice.CreatePixelShader
		(
			ps.data,		//Shader byte code (Pointer to binary data)
			ps.dataSize,	//Size of shader byte code
			nullptr,		//Pointer to a D3D11 class linkage object. Interface used to enable polymorphism by HLSL interface & classes (dynamic implementation binding)
			&m_pixelShader	//Output parameter where created D3D11 Shader object will be stored
		),
		"CreatePixelShader() failed."
	);
}
