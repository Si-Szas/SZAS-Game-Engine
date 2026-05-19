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
			void DrawTriangleList(ui32 vertexCount, ui32 startVertexLocation);

			//SETTER
			void SetGraphicsPipelineState(const GraphicsPipelineState& pipeline);
			void SetVertexBuffer(const VertexBuffer& buffer);
			void SetViewportSize(const Rect& size);

		private:
			Microsoft::WRL::ComPtr <ID3D11DeviceContext> m_context{};
	
		friend class GraphicsDevice;
	};
}