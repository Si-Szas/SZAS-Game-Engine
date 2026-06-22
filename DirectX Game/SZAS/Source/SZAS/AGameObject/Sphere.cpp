#include <SZAS/AGameObject/Sphere.h>
#include <SZAS/Game/WorldRenderer.h>
#include <SZAS/Graphics/GraphicsDevice/GraphicsDevice.h>
#include <SZAS/Math/MathUtility.h>

szas::Sphere::Sphere(const AGameObjectDescriptor& descriptor) :
	AGameObject(descriptor)
{
	//Defines how smooth the circle looks
	f32 radius = 1.0f;
	ui32 sliceCount = radius * 20;
	ui32 stackCount = radius * 20;

	std::vector<Vertex> sphereVertices;
	//Push back the topmost vertex of the sphere
	sphereVertices.push_back(
		{ { 0.0f, radius, 0.0f }, 
		{ 1.0f, 1.0f, 1.0f, 1.0f } 
	});

	f32 phiStep = MathUtility::PI / stackCount;
	f32 thetaStep = MathUtility::PI2 / sliceCount;

	for (ui32 i = 1; i < stackCount; ++i) {
		f32 phi = i * phiStep;
		for (ui32 j = 0; j <= sliceCount; ++j) {
			f32 theta = j * thetaStep;

			// Compute positions
			f32 x = radius * std::sin(phi) * std::cos(theta);
			f32 y = radius * std::cos(phi);
			f32 z = radius * std::sin(phi) * std::sin(theta);
			// Compute colors
			f32 r = (x / radius) * 0.5f + 0.5f;
			f32 g = (y / radius) * 0.5f + 0.5f;
			f32 b = (z / radius) * 0.5f + 0.5f;
			f32 a = 1.0f;

			sphereVertices.push_back({
				{x, y, z},
				{r, g, b, a}
			});
		}
	}
	//Push back the bottommost vertex of the sphere
	sphereVertices.push_back(
		{ { 0.0f, -radius, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	});

	//Create index buffer
	std::vector<ui32> sphereIndices;
	//Top vertex indices
	for (ui32 i = 0; i < stackCount; ++i) {
		for (ui32 j = 0; j < sliceCount; ++j) {
			sphereIndices.push_back(0);
			sphereIndices.push_back(0);
			sphereIndices.push_back(j + 1);
			sphereIndices.push_back(j + 2);
		}
	}

	// Inner ring quads
	ui32 ringVertexCount = sliceCount + 1;
	for (ui32 i = 0; i < stackCount - 2; ++i) {
		for (ui32 j = 0; j < sliceCount; ++j) {
			// Calculate quad corners
			ui32 bottomLeft = 1 + i * ringVertexCount + j;
			ui32 bottomRight = bottomLeft + 1;
			ui32 topLeft = 1 + (i + 1) * ringVertexCount + j;
			ui32 topRight = topLeft + 1;

			// 4 indices pushed since domain shader working with quad patches
			sphereIndices.push_back(bottomLeft);
			sphereIndices.push_back(bottomRight);
			sphereIndices.push_back(topLeft);
			sphereIndices.push_back(topRight);
		}
	}

	// Bottom vertex indices
	ui32 southPoleIndex = (ui32)sphereVertices.size() - 1;

	for (ui32 j = 0; j < sliceCount; ++j) {
		sphereIndices.push_back((southPoleIndex - ringVertexCount) + j);
		sphereIndices.push_back((southPoleIndex - ringVertexCount) + j + 1);
		sphereIndices.push_back(southPoleIndex);
		sphereIndices.push_back(southPoleIndex);
	}

	auto& worldRenderer = GetWorldRenderer();
	auto& device = worldRenderer.GetGraphicsDevice();

	m_vertexOffset = static_cast<ui32>(worldRenderer.GetVertexBuffer().size());
	m_indexLocation = static_cast<ui32>(worldRenderer.GetIndexBuffer().size());

	worldRenderer.GetVertexBuffer().push_back(device.CreateVertexBuffer
	({
		sphereVertices.data(),					//Vertex List
		static_cast<UINT>(sphereVertices.size()),		//Vertex List Size
		sizeof(Vertex)				//Vertex Size
	}));

	worldRenderer.GetIndexBuffer().push_back(device.CreateIndexBuffer
	({
		sphereIndices.data(),//Index List
		static_cast<UINT>(sphereIndices.size())//Index List Size
	}));
	
	m_sphereComponent = CreateOrGetComponent<SphereComponent>();
}

void szas::Sphere::OnCreate()
{

}

void szas::Sphere::OnUpdate(f32 deltaTime)
{
}

szas::Sphere::~Sphere()
{
}
