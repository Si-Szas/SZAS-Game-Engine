#include <SZAS/AGameObject/Quad.h>
#include <SZAS/Game/WorldRenderer.h>
#include <SZAS/Graphics/GraphicsDevice/GraphicsDevice.h>

szas::Quad::Quad(const AGameObjectDescriptor& descriptor) :
	AGameObject(descriptor)
{
}

void szas::Quad::OnCreate() 
{

	const Vertex quadVertices[] =
	{
		/* BR */ { {-1.0f, 0.0f,  -1.0f},  {1.0f, 1.0f, 1.0f, 1.0f} },
		/* BL */ { {-1.0f, 0.0f,   1.0f }, {1.0f, 1.0f, 0.0f, 1.0f}},
		/* TR */ { {1.0f,  0.0f,  -1.0f},  {1.0f, 0.0f, 1.0f, 1.0f} },
		/* TL */ { {1.0f,  0.0f,   1.0f},  {0.0f, 1.0f, 1.0f, 1.0f} }
	};

	const ui32 quadIndices[] =
	{
		0, 1, 2, 3
	};

	auto& worldRenderer = GetWorldRenderer();
	auto& device = worldRenderer.GetGraphicsDevice();

	m_vertexOffset = static_cast<ui32>(worldRenderer.GetVertexBuffer().size());
	m_indexLocation = static_cast<ui32>(worldRenderer.GetIndexBuffer().size());

	worldRenderer.GetVertexBuffer().push_back(device.CreateVertexBuffer
	({
		quadVertices,					//Vertex List
		std::size(quadVertices),		//Vertex List Size
		sizeof(Vertex)				//Vertex Size
		}));

	worldRenderer.GetIndexBuffer().push_back(device.CreateIndexBuffer
	({
		quadIndices,//Index List
		std::size(quadIndices)//Index List Size
		}));

	m_quadComponent = CreateOrGetComponent<QuadComponent>();
}

void szas::Quad::OnUpdate(f32 deltaTime) {

}

szas::Quad::~Quad() {

}