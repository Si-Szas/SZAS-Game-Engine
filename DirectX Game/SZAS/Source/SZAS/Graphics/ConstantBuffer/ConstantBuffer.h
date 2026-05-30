#pragma once
#include <SZAS/Graphics/GraphicsResource/GraphicsResource.h>

namespace szas
{
	class ConstantBuffer final : public GraphicsResource
	{
		public:
			//COONSTRUCTOR
			ConstantBuffer(const ConstantBufferDescriptor& constantBufferDescriptor, const GraphicsResourceDescriptor& graphicsResourceDescriptor);
	
		private:
			Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer{};
			ui32 m_size{};

		friend class DeviceContext;
	};
}
