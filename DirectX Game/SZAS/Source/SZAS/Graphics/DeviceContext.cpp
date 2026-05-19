#include <SZAS/Graphics/DeviceContext.h>
#include <SZAS/Graphics/SwapChain.h>
#include <SZAS/Graphics/GraphicsPipelineState.h>
#include <SZAS/Graphics/VertexBuffer.h>

szas::DeviceContext::DeviceContext(const GraphicsResourceDescriptor& descriptor) :
	GraphicsResource(descriptor)
{
	SZASGraphicsLogThrowOnFail(
	m_d3dDevice.CreateDeferredContext(
		0,		//Reserved parameter that doesn't affect deferred context
		&m_context	//Output parameter where we receive D311 Device instance
	), "CreateDeferredContext() failed.");
}

void szas::DeviceContext::ClearAndSetBackBuffer(const SwapChain& swapChain, const Vec4& color)
{
	//Clear the content of the render target view
	//Clear and fill back buffer with a specific color

	//Should be in a range of 0 to 1
	f32 colorArray[] = {color.x, color.y, color.z, color.w};
	
	auto RTV = swapChain.m_renderTargetView.Get();

	m_context->ClearRenderTargetView(
		RTV,	//RTV, object representing view into a so-called render target
		colorArray							//Array of 4 float values representing RGBA	
	);
	
	//Call OMSetRenderTarget to bind buffer we want to render graphics into
	m_context->OMSetRenderTargets(
		1,			//Number of render target views (we set all in one view, our back buffer)
		&RTV,		//An array of pointers to the views (we simulate an array using &)
		nullptr		//Depth Stensive View
	);
}

void szas::DeviceContext::DrawTriangleList(ui32 vertexCount, ui32 startVertexLocation)
{
	//How it assembles data into geometric primitives
	//Tells GPU how to connect the vertices
	//Triangle list specifies how the GPU should treat vertex data, every 3 vertices is an independent triangle
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Call Draw function
	m_context->Draw
	(
		vertexCount,		//Vertex Count. Defines number of vertices to draw
		startVertexLocation //Start vertex location. Allows us to specify the index of the first index in the vertex buffer to start drawing from
	);
}

void szas::DeviceContext::SetGraphicsPipelineState(const GraphicsPipelineState& pipeline)
{
	//Bind input layout to graphics pipeline. How to interpret bimnary structure of our vertex data and how it maps to vertex shaders expected inputs
	m_context->IASetInputLayout(pipeline.m_inputLayout.Get());

	//Actually binds vertex shader to GPU pipeline (use this vertex shader for the next draw calls)
	//It's like in GDGRAP1 where you had to call what shader you wanted to use before drawing specific things
	m_context->VSSetShader(
		pipeline.m_vertexShader.Get(),	//Get the Vertex Shader in Pipeline
		nullptr,						//Related to dynamic shader linkage
		0								//Related to dynamic shader linkage
	);

	//Do the same but for pixel shader
	m_context->PSSetShader(
		pipeline.m_pixelShader.Get(),	//Get Pixel Shader in Pipeline
		nullptr,
		0
	);
}


void szas::DeviceContext::SetVertexBuffer(const VertexBuffer& buffer)
{
	//Get list of buffers
	auto buff = buffer.m_buffer.Get();
	//Retrieve vertex size from vertex buffer class
	auto stride = buffer.m_vertexSize;
	//Initialize offset
	auto offset = 0u;

		//Defines one or more vertex buffers to the input assembler stage of the graphics pipeline
		//How we tell where vertex data is stored and how to interpret it
	m_context->IASetVertexBuffers
		(
			0,			//Start slot, starting point in list of vertex buffers
			1,			//Number of buffers being passed
			&buff,		//Actual list of buffers. Pointer to an array of D3D11 buffer pointers
			&stride,	//List of strides. Represent the size of a single vertex in bytes
			&offset			//Offset parameter to indicate where to start processing the data
	);
}

//Define viewport of rectangular region of render target where final image is drawn
void szas::DeviceContext::SetViewportSize(const Rect& size)
{
	D3D11_VIEWPORT vp{};
	vp.Width = static_cast<f32>(size.width);		//Width of window
	vp.Height = static_cast<f32>(size.height);		//Height of window
	vp.MinDepth = 0.0f;	//Near clipping plane. Depth range to which gepmetry is mapped after project during viewport transformation
	vp.MaxDepth = 1.0f;	//Far clipping plane

	//Context where and how our geometry will be rasterized on the screen
	m_context->RSSetViewports
	(
		1,	//Number of viewports we intent to use
		&vp	//Pointer to D3D11 viewport object
	);
}

