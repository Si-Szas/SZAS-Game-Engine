#pragma once
#include <SZAS/Graphics/GraphicsResource.h>
#include <SZAS/Math/Vec4.h>

namespace szas {

	class DeviceContext final : public GraphicsResource
	{
		public:
			//CONSTRUCTOR
			explicit DeviceContext(const GraphicsResourceDescriptor& descriptor);
		
			//FUNCTION
			void ClearAndSetBackBuffer(const SwapChain& swapChain, const Vec4& color);

		private:
			Microsoft::WRL::ComPtr <ID3D11DeviceContext> m_context{};
	
		friend class GraphicsDevice;
	};
}