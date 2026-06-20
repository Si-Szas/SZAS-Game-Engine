#include <SZAS/AGameObject/Cube.h>
#include <SZAS/Game/WorldRenderer.h>
#include <SZAS/Graphics/GraphicsDevice/GraphicsDevice.h>
#include <iostream>

szas::Cube::Cube(const AGameObjectDescriptor& descriptor) :
	AGameObject(descriptor)
{
	auto& worldRenderer = GetWorldRenderer();

	const Vertex cubeVertices[] =
	{
		{ {-0.5f,-0.5f,-0.5f},	{1,0,0,1}},
		{ {-0.5f,0.5f,-0.5f},	{0,1,0,1}},
		{ {0.5f,0.5f,-0.5f},	{0,0,1,1}},
		{ {0.5f,-0.5f,-0.5f},	{1,1,1,1}},

		{ {0.5f,-0.5f,0.5f},	{0,0,0,1}},
		{ {0.5f,0.5f,0.5f},		{1,0,1,1}},
		{ {-0.5f,0.5f,0.5f},	{0,1,1,1}},
		{ {-0.5f,-0.5f,0.5f},	{1,1,0,1}}
	};

	//We are drawing in 4 control point patches
	const ui32 cubeIndices[] =
	{
		//Front Face
		0, 1, 3, 2,
		//Back Face
		4, 5, 7, 6,
		//Top Face
		5, 2, 6, 1,
		//Bottom Face
		7, 0, 4, 3,
		//Right Face
		3, 2, 4, 5,
		//Left Face
		7, 6, 0, 1
	};

	auto& device = worldRenderer.GetGraphicsDevice();

	m_vertexOffset = static_cast<ui32>(worldRenderer.GetVertexBuffer().size());
	m_indexLocation = static_cast<ui32>(worldRenderer.GetIndexBuffer().size());

	worldRenderer.GetVertexBuffer().push_back(device.CreateVertexBuffer
	({
		cubeVertices,
		std::size(cubeVertices),
		sizeof(Vertex)
		}));

	worldRenderer.GetIndexBuffer().push_back(device.CreateIndexBuffer
	({
		cubeIndices,//Index List
		std::size(cubeIndices)//Index List Size
	}));

	m_cubeComponent = CreateOrGetComponent<CubeComponent>();
}

void szas::Cube::OnCreate() 
{
}

void szas::Cube::OnUpdate(f32 deltaTime)
{
}

szas::Cube::~Cube()
{
}
