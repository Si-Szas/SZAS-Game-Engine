#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/Core/Base.h>
#include <SZAS/Graphics/GraphicsUtility/GraphicsLogUtility.h>

#include <d3d11.h>
#include <wrl.h>

namespace szas
{
	//Dependency aggregation strategy
	struct GraphicsResourceDescriptor
	{
		BaseDescriptor base;
		std::shared_ptr<const GraphicsDevice> graphicsDevice;
		ID3D11Device& d3dDevice;
		IDXGIFactory& dxgiFactory;
	};

	class GraphicsResource : public Base
	{
		public:
			//CONSTRUCTOR
			explicit GraphicsResource(const GraphicsResourceDescriptor& descriptor):
				//Member initializer list
				Base(descriptor.base),
				m_graphicsDevice(descriptor.graphicsDevice),
				m_d3dDevice(descriptor.d3dDevice),
				m_dxgiFactory(descriptor.dxgiFactory)
			{
			}

		protected:
			std::shared_ptr<const GraphicsDevice> m_graphicsDevice;
			ID3D11Device& m_d3dDevice;
			IDXGIFactory& m_dxgiFactory;
	};
}