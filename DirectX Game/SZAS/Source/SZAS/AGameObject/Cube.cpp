#include <SZAS/AGameObject/Cube.h>
#include <SZAS/AComponent/TransformComponent.h>
#include <SZAS/Game/WorldRenderer.h>
#include <SZAS/Graphics/GraphicsDevice/GraphicsDevice.h>

#include <iostream>
#include <algorithm>
#include <cmath>

szas::Cube::Cube(const AGameObjectDescriptor& descriptor) :
	AGameObject(descriptor)
{
}

void szas::Cube::OnCreate() 
{
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

	auto& worldRenderer = GetWorldRenderer();
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

	m_originalPosition = GetTransform().GetPosition();
	m_originalScale = GetTransform().GetScale();
}

void szas::Cube::OnUpdate(f32 deltaTime)
{
	//Clamp the lerp so it doesnt go above 1
	if (lerpValue >= 1.0f) {
		lerpValue = 1.0f;
		reverseLerp = true;
	} // Or below 0
	else if (lerpValue <= 0.0f) {
		lerpValue = 0.0f;
		reverseLerp = false;
	}
	//If lerp = 1, then at means it needs to go backwards (subtract)
	if (reverseLerp)
	{
		lerpValue -= 0.5f * deltaTime;
	} //Else, add to lerpValue
	else 
	{ 
		lerpValue += 0.5f * deltaTime;
	}

	//Get the lerp of the position and scale components (x, y, z)
	Vec3 lerpPos = Vec3::Lerp(m_originalPosition, m_position2, lerpValue);
	Vec3 lerpScale = Vec3::Lerp(m_originalScale, m_scale2, lerpValue);
	
	//Set the new position and scale
	GetTransform().SetPosition(lerpPos);
	GetTransform().SetScale(lerpScale);
}

szas::Cube::~Cube()
{
}
