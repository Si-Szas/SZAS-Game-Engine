#pragma once
#include <SZAS/Graphics/GraphicsResource.h>

namespace szas
{
	class SwapChain final : public GraphicsResource
	{
		public:
			//CONSTRUCTOR
			explicit SwapChain(const SwapChainDescriptor& swapChainDescriptor, const GraphicsResourceDescriptor& graphicsResourceDescriptor);
	
		private:
			Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;
	};
}