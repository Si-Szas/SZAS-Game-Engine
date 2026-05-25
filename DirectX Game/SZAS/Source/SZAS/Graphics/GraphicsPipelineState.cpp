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

	//float3 position : POSITION0;
	//float4 color : COLOR0;
	constexpr D3D11_INPUT_ELEMENT_DESC elements[] =
	{	
		//// POSITION ATTRIBUTE ////
		{
			"POSITION",						//Semantic name
			0,								//Semantic index (if they share the same type)
			DXGI_FORMAT_R32G32B32_FLOAT,	//Format of position attirbute
			0,								//Input slot (which vertex buffer the element comes from)
			0,								//Aligned byte offset. Byte offset from start.
			D3D11_INPUT_PER_VERTEX_DATA,	//Input slot class attribute that specifies if a vertex attributes comes per vertex or per instance
			0								//Instance step date attribute required for instance rendering
		},

		//// COLOR ATTRIBUTE ////
		{
			"COLOR",						//Semantic name
			0,								//Semantic index (if they share the same type)
			DXGI_FORMAT_R32G32B32A32_FLOAT,	//Format of position attirbute
			0,								//Input slot (which vertex buffer the element comes from)
			12,								//Aligned byte offset. Byte offset from start. This is after the position attribute and pos is 3 floats, each 4 bytes, then 3*4
			D3D11_INPUT_PER_VERTEX_DATA,	//Input slot class attribute that specifies if a vertex attributes comes per vertex or per instance
			0								//Instance step date attribute required for instance rendering
		}
	};

	//Create Input Layout
	SZASGraphicsLogThrowOnFail(
	m_d3dDevice.CreateInputLayout
	(
		elements,				//Pointer to a list of D3D11 Input Elements desc objects
		std::size(elements),	//Size of input elements
		vs.data,				//Shader byte code. Defines vertex data structure, which is defined in vertex shader
		vs.dataSize,
		&m_inputLayout			//Output parameter. Input layout
	), "CreateInputLayout() failed.");

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
