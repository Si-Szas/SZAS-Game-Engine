#include <SZAS/Graphics/RenderSystem.h>
#include <SZAS/Graphics/GraphicsLogUtility.h>

szas::RenderSystem::RenderSystem(const RenderSystemDescriptor& descriptor): Base(descriptor.base)
{
	D3D_FEATURE_LEVEL featureLevel{};
	UINT createDeviceFlags{};
	//We only want to add the Flag corresponding to the Debug Layer
	//Helps get warnings and errors during runtime
	#ifdef _DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

	//Creates D3D11 Device to allow us to render graphics in the window
	SZASGraphicsLogErrorAndThrow(D3D11CreateDevice
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
	), 
		//Error if initialization failed
		"Direct3D11 initialization failed.");
	//Ask object if it supports an interface, and if so, return a pointer to that interface
	SZASGraphicsLogErrorAndThrow(
		m_d3dDevice->QueryInterface(IID_PPV_ARGS(&m_dxgiDevice)),
		"QueryInterface() failed to retrieve IDXGI Device."
	);
	//We have access now to DXGI through the device, so we now need to get the adapter
	SZASGraphicsLogErrorAndThrow(
		m_dxgiDevice->GetParent(IID_PPV_ARGS(&m_dxgiAdapter)),
		"GetParent() failed to retrieve IDXGI Adapter."
	);
	//Call get Parent on Adapter to get the Factory
	SZASGraphicsLogErrorAndThrow(
		m_dxgiAdapter->GetParent(IID_PPV_ARGS(&m_dxgiFactory)),
		"GetParent() failed to retrieve IDXGI Factory."
	);
}

szas::RenderSystem::~RenderSystem()
{
}
