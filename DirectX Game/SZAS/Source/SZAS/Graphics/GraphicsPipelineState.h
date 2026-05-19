#pragma once
#include <SZAS/Graphics/GraphicsResource.h>
#include <SZAS/Graphics/GraphicsLogUtility.h>

namespace szas
{
	//Refers to collection of configuration settings and objects that control how the GPU process and renders graphics
		//How shaders are used, how pixels are blended, etc.
	class GraphicsPipelineState final : public GraphicsResource
	{
		public:
			//CONSTRUCTOR
			GraphicsPipelineState(const GraphicsPipelineStateDescriptor& graphicsPipelineStateDescriptor, const GraphicsResourceDescriptor& graphicsResourceDescriptor);
	
		private:
			Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader{};
			Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader{};
	
		friend class DeviceContext;
	};
}

