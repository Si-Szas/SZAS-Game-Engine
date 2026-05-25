#include <SZAS/Graphics/GraphicsDevice.h>
#include <SZAS/Graphics/GraphicsLogUtility.h>
#include <SZAS/Graphics/SwapChain.h>
#include <SZAS/Graphics/DeviceContext.h>
#include <SZAS/Graphics/ShaderBinary.h>
#include <SZAS/Graphics/GraphicsPipelineState.h>
#include <SZAS/Graphics/VertexBuffer.h>
#include <SZAS/Graphics/VertexShaderSignature.h>

szas::GraphicsDevice::GraphicsDevice(const GraphicsDeviceDescriptor& descriptor): Base(descriptor.base)
{
	D3D_FEATURE_LEVEL featureLevel{};
	UINT createDeviceFlags{};
	//We only want to add the Flag corresponding to the Debug Layer
	//Helps get warnings and errors during runtime
	#ifdef _DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

	//Creates D3D11 Device to allow us to render graphics in the window
	SZASGraphicsLogThrowOnFail(D3D11CreateDevice
	(
		//INPUT PARAMETERS--------
		NULL,						//DXGI Adapter (Adapter installed on the system)
		D3D_DRIVER_TYPE_HARDWARE,	//Picks primary GPU
		NULL,						//DLL Implement custom software restorizer
		createDeviceFlags,			//Device flags
		NULL,						//Best feature level. If null, its best feature level supported by the system
		0,							//Size of previous array (feature level)
		D3D11_SDK_VERSION,			//Safety check to prevent version mismatches
		//OUTPUT PARAMETERS--------
		&m_d3dDevice,				//Visual GPU to manage GPU-related resources
		&featureLevel,				//Feature Level chosen internally
		&m_d3dContext				//Device context
	), "Direct3D11 initialization failed.");
	//Ask object if it supports an interface, and if so, return a pointer to that interface
	SZASGraphicsLogThrowOnFail(
		m_d3dDevice->QueryInterface(IID_PPV_ARGS(&m_dxgiDevice)
		), "QueryInterface() failed to retrieve IDXGI Device."
	);
	//We have access now to DXGI through the device, so we now need to get the adapter
	SZASGraphicsLogThrowOnFail(
		m_dxgiDevice->GetParent(IID_PPV_ARGS(&m_dxgiAdapter)
		), "GetParent() failed to retrieve IDXGI Adapter."
	);
	//Call get Parent on Adapter to get the Factory
	SZASGraphicsLogThrowOnFail(
		m_dxgiAdapter->GetParent(IID_PPV_ARGS(&m_dxgiFactory)
		), "GetParent() failed to retrieve IDXGI Factory."
	);
}

szas::GraphicsDevice::~GraphicsDevice()
{
}

szas::SwapChainPtr szas::GraphicsDevice::CreateSwapChain(const SwapChainDescriptor& descriptor)
{
	//You can use using namespace szas but it should only be in cpp files and only if necessary
	return std::make_shared<SwapChain>(descriptor, GetGraphicsResourceDescriptor());
}

szas::DeviceContextPtr szas::GraphicsDevice::CreateDeviceContext()
{
	return std::make_shared<DeviceContext>(GetGraphicsResourceDescriptor());
}

szas::ShaderBinaryPtr szas::GraphicsDevice::CompileShader(const ShaderCompileDescriptor& descriptor)
{
	return std::make_shared<ShaderBinary>(descriptor, GetGraphicsResourceDescriptor());
}

szas::GraphicsPipelineStatePtr szas::GraphicsDevice::CreateGraphicsPipelineState(const GraphicsPipelineStateDescriptor& descriptor)
{
	return std::make_shared<GraphicsPipelineState>(descriptor, GetGraphicsResourceDescriptor());
}

szas::VertexBufferPtr szas::GraphicsDevice::CreateVertexBuffer(const VertexBufferDescriptor& descriptor)
{
	return std::make_shared<VertexBuffer>(descriptor, GetGraphicsResourceDescriptor());
}

szas::VertexShaderSignaturePtr szas::GraphicsDevice::CreateVertexShaderSignature(const VertexShaderSignatureDescriptor& descriptor)
{
	return std::make_shared<VertexShaderSignature>(descriptor, GetGraphicsResourceDescriptor());
}

//This function retrieves command lists, then executes it
void szas::GraphicsDevice::ExecuteCommandList(DeviceContext& context)
{
	Microsoft::WRL::ComPtr<ID3D11CommandList> commandList{};

	//Retrieve command list from passed in device context
	SZASGraphicsLogThrowOnFail(
	context.m_context->FinishCommandList
	(
		false,			//Bool flag whether to restore previous graphics pipeline state. Pass false to optimize
		&commandList	//Output parameter where we retrieve command list
	), "FinishCommandList() failed.");
	
	//Sends commands directly to GPU as they are issued (immediate)
	m_d3dContext->ExecuteCommandList
	(
		commandList.Get(), //Row pointer to command list
		false			   //Restore context state. Decide if we restore all context states to date valyes before it is executed. False for optimization
	);
}

szas::GraphicsResourceDescriptor szas::GraphicsDevice::GetGraphicsResourceDescriptor() const noexcept
{
	return { {m_logger}, shared_from_this(), *m_d3dDevice.Get(), *m_dxgiFactory.Get()};

}