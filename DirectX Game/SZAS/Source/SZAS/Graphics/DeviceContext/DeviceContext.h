#pragma once
#include <SZAS/Graphics/GraphicsResource/GraphicsResource.h>
#include <SZAS/Math/Vec4.h>

namespace szas {

	class DeviceContext final : public GraphicsResource
	{
		public:
			//CONSTRUCTOR
			explicit DeviceContext(const GraphicsResourceDescriptor& descriptor);
		
			//FUNCTION
			void ClearAndSetBackBuffer(const SwapChain& swapChain, const Vec4& color);

			//SETTER
			void SetGraphicsPipelineState(const GraphicsPipelineState& pipeline);
			void SetViewportSize(const Rect& size);

			void SetVertexBuffer(const VertexBuffer& buffer);
			void SetConstantBuffer(const ConstantBuffer& buffer);

			//UPDATE 
			void UpdateConstantBuffer(const ConstantBuffer& buffer, const void* data);
			
			//DRAW
			void DrawTriangleList(ui32 vertexCount, ui32 startVertexLocation);
			void DrawTriangleListWithTessellation(ui32 vertexCount, ui32 startVertexLocation);
			void DrawQuadList(ui32 vertexCount, ui32 startVertexLocation);

		private:
			Microsoft::WRL::ComPtr <ID3D11DeviceContext> m_context{};
	
		friend class GraphicsDevice;
	};
}