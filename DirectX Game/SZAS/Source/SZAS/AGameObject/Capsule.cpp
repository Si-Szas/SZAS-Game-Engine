#include <SZAS/AGameObject/Capsule.h>
#include <SZAS/Game/WorldRenderer.h>
#include <SZAS/Graphics/GraphicsDevice/GraphicsDevice.h>

szas::Capsule::Capsule(const AGameObjectDescriptor& descriptor) :
	AGameObject(descriptor)
{
    //Defines how smooth the cylinder looks
    f32 height = 1.0f;
    f32 radius = 0.5f;
    ui32 sliceCount = 20;
    ui32 stackCount = 1;

    std::vector<Vertex> capsuleVertices;
    //Push topmost vertex of cylinder
    ui32 topCenterIndex = static_cast<ui32>(capsuleVertices.size());
    capsuleVertices.push_back({
        { 0.0f, height, 0.0f },
        { 1.0f, 1.0f, 1.0f, 1.0f }
        });

    //Cylinder body / ring
    for (ui32 i = 0; i <= stackCount; i++)
    {
        f32 y = ((f32)i / stackCount) * height - (height * 0.5f);

        for (ui32 j = 0; j <= sliceCount; j++)
        {
            // Calculate angle around the cylinder
            f32 theta = ((f32)j / sliceCount) * MathUtility::PI2;

            f32 x = radius * cosf(theta);
            f32 z = radius * sinf(theta);

            f32 r = (x / (2.0f * radius)) + 0.5f;
            f32 g = (y / height) + 0.5f;
            f32 b = (z / (2.0f * radius)) + 0.5f;
            f32 a = 1.0f;

            capsuleVertices.push_back({
                {x, y, z},
                {r, g, b, a}
                });
        }
    }

    //Push bottommost vertex of cylinder
    ui32 bottomCenterIndex = static_cast<ui32>(capsuleVertices.size());
    capsuleVertices.push_back({
        { 0.0f, -height, 0.0f },
        { 0.0f, 0.0f, 0.0f, 1.0f }
        });

    //Create indices
    std::vector<ui32> capsuleIndices;
    //Top vertex indices
    ui32 ringVertexCount = sliceCount + 1;
    ui32 topStart = (stackCount * ringVertexCount) + 1;
    for (ui32 i = 0; i < sliceCount; i++)
    {
        ui32 topCurrent = topStart + i;
        ui32 topNext = topStart + i + 1;

        capsuleIndices.push_back(topCurrent);
        capsuleIndices.push_back(topCenterIndex);
        capsuleIndices.push_back(topNext);
        capsuleIndices.push_back(topCenterIndex);
    }
    //Ring vertex indices
    for (ui32 i = 0; i < stackCount; i++)
    {
        for (ui32 j = 0; j < sliceCount; j++)
        {
            //Calculate 4 corners of patch
            ui32 bottomLeft = (i * ringVertexCount + j) + 1;
            ui32 bottomRight = bottomLeft + 1;
            ui32 topLeft = ((i + 1) * ringVertexCount + j) + 1;
            ui32 topRight = topLeft + 1;
            // 4 indices pushed since domain shader working with quad patches
            capsuleIndices.push_back(bottomLeft);
            capsuleIndices.push_back(topLeft);
            capsuleIndices.push_back(bottomRight);
            capsuleIndices.push_back(topRight);
        }
    }

    //Bottom vertex indices
    for (ui32 i = 0; i < sliceCount; i++)
    {
        ui32 bottomCurrent = i + 1;
        ui32 bottomNext = i + 2;

        //Push back the bottom of the cylinder's quads
        capsuleIndices.push_back(bottomNext);
        capsuleIndices.push_back(bottomCenterIndex);
        capsuleIndices.push_back(bottomCurrent);
        capsuleIndices.push_back(bottomCenterIndex);
    }

	auto& worldRenderer = GetWorldRenderer();
	auto& device = worldRenderer.GetGraphicsDevice();

	m_vertexOffset = static_cast<ui32>(worldRenderer.GetVertexBuffer().size());
	m_indexLocation = static_cast<ui32>(worldRenderer.GetIndexBuffer().size());

	worldRenderer.GetVertexBuffer().push_back(device.CreateVertexBuffer
	({
		capsuleVertices.data(),					//Vertex List
		static_cast<UINT>(capsuleVertices.size()),		//Vertex List Size
		sizeof(Vertex)				//Vertex Size
		}));

	worldRenderer.GetIndexBuffer().push_back(device.CreateIndexBuffer
	({
        capsuleIndices.data(),//Index List
		static_cast<UINT>(capsuleIndices.size())//Index List Size
		}));

	m_capsuleComponent = CreateOrGetComponent<CapsuleComponent>();
}

void szas::Capsule::OnCreate()
{

}

void szas::Capsule::OnUpdate(f32 deltaTime)
{

}

szas::Capsule::~Capsule()
{

}