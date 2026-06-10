#include <SZAS/AGameObject/Quad/Quad.h>

szas::Quad::Quad(RefPtr<VertexShaderSignature> vs, RefPtr<ShaderBinary> ps, RefPtr<ShaderBinary> hs, RefPtr<ShaderBinary> ds)
{
	m_vertexData = m_vertexList;

	m_vertexShader = vs;
	m_hullShader = hs;
	m_domainShader = ds;
	m_pixelShader = ps;
}

szas::Quad::Quad(const Vertex* vertices, RefPtr<VertexShaderSignature> vs, RefPtr<ShaderBinary> ps, RefPtr<ShaderBinary> hs, RefPtr<ShaderBinary> ds)
{
	for (size_t i = 0; i < 4; ++i) {
		m_vertexList[i] = vertices[i];
	}

	m_vertexData = m_vertexList;

	m_vertexShader = vs;
	m_hullShader = hs;
	m_domainShader = ds;
	m_pixelShader = ps;
}

szas::Quad::~Quad()
{
}

void szas::Quad::CreateVertices(const Vertex* vertices)
{
	for (size_t i = 0; i < 4; ++i) {
		m_vertexList[i] = vertices[i];
	}
}

void szas::Quad::Draw(RefPtr<VertexBuffer> vertexBuffer, Microsoft::WRL::ComPtr<ID3D11DeviceContext> context)
{
	//For tessellation
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);

	//Call Draw function
	context->Draw
	(
		vertexBuffer->GetVertexListSize(),	//Vertex Count. Defines number of vertices to draw
		0u //Start vertex location. Allows us to specify the index of the first index in the vertex buffer to start drawing from
	);
}

const void* szas::Quad::GetVertexList() const {
	return m_vertexData;
}