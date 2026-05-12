#include "GraphicsEngine.h"

GraphicsEngine* GraphicsEngine::get()
{
	//Create engine instance, and always return that same instance
	static GraphicsEngine engine;

	return &engine;
}

GraphicsEngine::GraphicsEngine()
{
}

bool GraphicsEngine::init()
{
	//Vector of Driver Types from best to worst
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	//Get Driver Types size
	UINT driverTypesSize = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] = 
	{
		D3D_FEATURE_LEVEL_11_0	//Feature Level 11.0
	};
	UINT featureLevelsSize = ARRAYSIZE(featureLevels);

	//Result to be used to check if Device Created successfully
	HRESULT result = 0;
	//Iterate through all driver types
	for (UINT driverTypeIndex = 0; driverTypeIndex < driverTypesSize; driverTypeIndex++)
	{
		result = 
			D3D11CreateDevice
			(
				NULL,
				driverTypes[driverTypeIndex],	//Driver Type using Array defined above
				NULL,
				NULL,
				featureLevels,					//Feature Level (DirectX Version)
				featureLevelsSize,				//Size of Feature Levels Array
				D3D11_SDK_VERSION,				//DirectX SDK Version
				&m_D3DDevice,					//Device Pointer
				&m_featureLevel,				//Feature Level Pointer (Shows which level was chosen)
				&m_IMMContext		//Immediate Device Context Pointer
			);

		if (SUCCEEDED(result)) break;
	}

	if (FAILED(result)) return false;

	return true;
}

bool GraphicsEngine::release()
{
	//Release all resources (device context and directX device)
	m_IMMContext->Release();
	m_D3DDevice->Release();

	return true;
}

GraphicsEngine::~GraphicsEngine()
{
}
