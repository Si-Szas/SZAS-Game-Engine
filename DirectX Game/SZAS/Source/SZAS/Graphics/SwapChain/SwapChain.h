#pragma once
#include <SZAS/Graphics/GraphicsResource/GraphicsResource.h>

namespace szas
{
	class SwapChain final : public GraphicsResource
	{
		public:
			//CONSTRUCTOR
			SwapChain(const SwapChainDescriptor& swapChainDescriptor, const GraphicsResourceDescriptor& graphicsResourceDescriptor);
		
			//FUNCTIONS
			// Enable vsync to match refresh rate of my laptops monitor (60Hz)
			void Present(bool vsync = true);

			//GETTER
			Rect GetSize() const noexcept;
	private:
			//FUNCTIONS
			void ReloadBuffers();

		private:
			Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain{};
			Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView{};
			Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView{};
			Rect m_size{};

			friend class DeviceContext;
	};
}