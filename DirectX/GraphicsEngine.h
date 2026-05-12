#pragma once

#include <d3d11.h>

class GraphicsEngine
{
	//This class is a SINGLETON
	public:
		static GraphicsEngine* get();

	public:
		//CONSTRUCTOR
		GraphicsEngine();

		//FUNCTIONS
		  //Initialize Graphics Engine and DirectX11 Device
		bool init();
		  //Destroy Resources Loaded
		bool release();

		//DECONSTRUCTOR
		~GraphicsEngine();

	private:
		ID3D11Device* m_D3DDevice;
		D3D_FEATURE_LEVEL m_featureLevel;
		ID3D11DeviceContext* m_IMMContext;
};

