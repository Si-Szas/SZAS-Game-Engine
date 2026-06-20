#include <SZAS/AGameObject/Sphere.h>
#include <SZAS/Game/WorldRenderer.h>
#include <SZAS/Graphics/GraphicsDevice/GraphicsDevice.h>
#include <SZAS/Math/MathUtility.h>

szas::Sphere::Sphere(const AGameObjectDescriptor& descriptor) :
	AGameObject(descriptor)
{
	//Defines how smooth the circle looks
	int radius = 1;
	int sliceCount = radius * 20;
	int stackCount = radius * 20;

	std::vector<Vertex> sphereVertices;
	//Push back the topmost vertex of the sphere
	sphereVertices.push_back(Vertex({ 0.0f, szas::f32(radius), 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }));

	float phiStep = MathUtility::PI / stackCount;
	float thetaStep = MathUtility::PI2 / sliceCount;

	for (int i = 1; i < stackCount; ++i) {
		float phi = i * phiStep;
		for (int j = 0; j <= sliceCount; ++j) {
			f32 theta = j * thetaStep;

			Vertex v;

			// Compute positions
			v.position.x = radius * std::sin(phi) * std::cos(theta);
			v.position.y = radius * std::cos(phi);
			v.position.z = radius * std::sin(phi) * std::sin(theta);

			// Compute colors
			v.color.x = (v.position.x / radius) * 0.5f + 0.5f;
			v.color.y = (v.position.y / radius) * 0.5f + 0.5f;
			v.color.z = (v.position.z / radius) * 0.5f + 0.5f;
			v.color.w = 1.0f;

			sphereVertices.push_back(*(static_cast<const Vertex*>(&v)));
		}
	}
	//Push back the bottommost vertex of the sphere
	sphereVertices.push_back(Vertex({ 0.0f, szas::f32(-radius), 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0f }));

	std::vector<ui32> sphereIndices;
	for (int i = 0; i < stackCount; ++i) {
		for (int j = 0; j < sliceCount; ++j) {
			sphereIndices.push_back(0);
			sphereIndices.push_back(0);
			sphereIndices.push_back(static_cast<ui32>(1 + j));
			sphereIndices.push_back(static_cast<ui32>(1 + j + 1));
		}
	}

	// Inner ring quads
	int baseIndex = 1;
	int ringVertexCount = sliceCount + 1;
	for (int i = 0; i < stackCount - 2; ++i) {
		for (int j = 0; j < sliceCount; ++j) {
			// Calculate quad corners
			ui32 topLeft = static_cast<ui32>(baseIndex + i * ringVertexCount + j);
			ui32 topRight = static_cast<ui32>(baseIndex + i * ringVertexCount + j + 1);
			ui32 bottomLeft = static_cast<ui32>(baseIndex + (i + 1) * ringVertexCount + j);
			ui32 bottomRight = static_cast<ui32>(baseIndex + (i + 1) * ringVertexCount + j + 1);

			// 4 indices pushed since domain shader working with quad patches
			sphereIndices.push_back(topLeft);
			sphereIndices.push_back(topRight);
			sphereIndices.push_back(bottomLeft);
			sphereIndices.push_back(bottomRight);
		}
	}

	// Bottom pole 
	ui32 southPoleIndex = (ui32)sphereVertices.size() - 1;
	baseIndex = southPoleIndex - ringVertexCount;

	for (int j = 0; j < sliceCount; ++j) {
		sphereIndices.push_back(static_cast<ui32>(baseIndex + j));
		sphereIndices.push_back(static_cast<ui32>(baseIndex + j + 1));
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
