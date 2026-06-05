#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/Graphics/DeviceContext/DeviceContext.h>
#include <SZAS/Graphics/VertexBuffer/VertexBuffer.h>
#include <SZAS/Graphics/VertexShaderSignature/VertexShaderSignature.h>
#include <SZAS/Graphics/ShaderBinary/ShaderBinary.h>

namespace szas
{
	class Quad
	{
		public:
			Quad();
			Quad(RefPtr<VertexShaderSignature> vs, RefPtr<ShaderBinary> ps, RefPtr<ShaderBinary> hs, RefPtr<ShaderBinary> ds);
			Quad(const Vertex* vertices, RefPtr<VertexShaderSignature> vs, RefPtr<ShaderBinary> ps, RefPtr<ShaderBinary> hs, RefPtr<ShaderBinary> ds);
			~Quad();

			void CreateVertices(const Vertex* vertices);
			void Draw(RefPtr<VertexBuffer> vertexBuffer, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);

			const void* GetVertexList() const;

		private:
			Vertex m_vertexList[4];
			const void* m_vertexData;

			RefPtr<VertexShaderSignature> m_vertexShader{};
			RefPtr<ShaderBinary> m_hullShader{};
			RefPtr<ShaderBinary> m_domainShader{};
			RefPtr<ShaderBinary> m_pixelShader{};
	};
}

