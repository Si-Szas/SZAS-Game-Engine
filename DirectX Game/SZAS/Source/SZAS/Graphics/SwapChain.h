#pragma once
#include <SZAS/Graphics/GraphicsResource.h>

namespace szas
{
	class SwapChain final : public GraphicsResource
	{
		public:
			//CONSTRUCTOR
			SwapChain(const SwapChainDescriptor& swapChainDescriptor, const GraphicsResourceDescriptor& graphicsResourceDescriptor);
		
			//FUNCTIONS
			void Present(bool vsync = false);

			//GETTER
			Rect GetSize() const noexcept;
	private:
			//FUNCTIONS
			void ReloadBuffers();

		private:
			Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain{};
			Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView{};
			Rect m_size{};

			friend class DeviceContext;
	};
}