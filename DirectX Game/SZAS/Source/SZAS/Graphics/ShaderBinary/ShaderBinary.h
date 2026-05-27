#pragma once
#include <SZAS/Graphics/GraphicsResource/GraphicsResource.h>

namespace szas
{
	class ShaderBinary final : public GraphicsResource
	{
		public:
			//CONSTRUCTOR
			ShaderBinary(const ShaderCompileDescriptor& shaderCompileDescriptor, const GraphicsResourceDescriptor& graphicsResourceDescriptor);
	
			//GETTER
			BinaryData GetData() const noexcept;
			ShaderType GetShaderType() const noexcept;

		private:
			Microsoft::WRL::ComPtr<ID3DBlob> m_blob{};
			ShaderType m_type{};
	};
}