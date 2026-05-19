#pragma once
#include <SZAS/Graphics/GraphicsResource.h>
#include <SZAS/Core/Common.h>
#include <SZAS/Core/Core.h>
#include <SZAS/Core/Base.h>
#include <d3d11.h>
#include <wrl.h>

namespace szas 
{
	class GraphicsDevice final: public Base, public std::enable_shared_from_this<GraphicsDevice>
	{
		public:
			//CONSTRUCTOR
			explicit GraphicsDevice(const GraphicsDeviceDescriptor& descriptor);
			
			//FUNCTIONS
			SwapChainPtr CreateSwapChain(const SwapChainDescriptor& descriptor);
			DeviceContextPtr CreateDeviceContext();
			ShaderBinaryPtr CompileShader(const ShaderCompileDescriptor& descriptor);
			GraphicsPipelineStatePtr CreateGraphicsPipelineState(const GraphicsPipelineStateDescriptor& descriptor);

			void ExecuteCommandList(DeviceContext& context);

			//DESTRUCTOR
			virtual ~GraphicsDevice() override;
			
		private:
			GraphicsResourceDescriptor GetGraphicsResourceDescriptor() const noexcept;
			
		private:
			//We cannot use smart pointers for D3D Devices. Instead we use Com Objects
			//Use reference counting for memory management. Counts how many references or owners point to it.
			//When reference count = 0, object is destroyed
			Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice{};
			//Device object
			Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext{};
			//Pointer to IDXGI Device
			Microsoft::WRL::ComPtr<IDXGIDevice> m_dxgiDevice{};
			//Pointer to IDXGI Device
			Microsoft::WRL::ComPtr<IDXGIAdapter> m_dxgiAdapter{};
			// Factory to let us create DXGI Resources like a Swap Chain
			Microsoft::WRL::ComPtr<IDXGIFactory> m_dxgiFactory{};
	};
}
