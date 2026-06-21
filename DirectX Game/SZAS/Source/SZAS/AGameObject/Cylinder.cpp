#include <SZAS/AGameObject/Cylinder.h>
#include <SZAS/Game/WorldRenderer.h>
#include <SZAS/Graphics/GraphicsDevice/GraphicsDevice.h>

szas::Cylinder::Cylinder(const AGameObjectDescriptor& descriptor) :
	AGameObject(descriptor)
{
    //Defines how smooth the cylinder looks
    f32 height = 1.0f;
    f32 radius = 0.5f;
    ui32 sliceCount = 20;
    ui32 stackCount = 1;

    std::vector<Vertex> cylinderVertices;
    for (ui32 i = 0; i <= stackCount; i++)
    {
        f32 y = ((f32)i / stackCount) * height - (height * 0.5f);

        for (ui32 j = 0; j <= sliceCount; j++)
        {
            // Calculate angle around the cylinder
            f32 theta = ((f32)j / sliceCount) * MathUtility::PI2;

            f32 x = radius * cosf(theta);
            f32 z = radius * sinf(theta);

            f32 r = (x  / (2.0f * radius)) + 0.5f;
            f32 g = (y / height) + 0.5f;
            f32 b = (z / (2.0f * radius)) + 0.5f;
            f32 a = 1.0f;
            
            cylinderVertices.push_back({
                {x, y, z},
                {r, g, b, a}
            });
        }
    }

    std::vector<ui32> cylinderIndices;
    ui32 ringVertexCount = sliceCount + 1;
    for (ui32 i = 0; i < stackCount; i++)
    {
        for (ui32 j = 0; j < sliceCount; j++)
        {
            //Calculate 4 corners of patch
            ui32 bottomLeft = i * ringVertexCount + j;
            ui32 bottomRight = bottomLeft + 1;
            ui32 topLeft = (i + 1) * ringVertexCount + j;
            ui32 topRight = topLeft + 1;
            // 4 indices pushed since domain shader working with quad patches
            cylinderIndices.push_back(bottomLeft);
            cylinderIndices.push_back(topLeft);
            cylinderIndices.push_back(bottomRight);
            cylinderIndices.push_back(topRight);
        }
    }

	auto& worldRenderer = GetWorldRenderer();
	auto& device = worldRenderer.GetGraphicsDevice();

	m_vertexOffset = static_cast<ui32>(worldRenderer.GetVertexBuffer().size());
	m_indexLocation = static_cast<ui32>(worldRenderer.GetIndexBuffer().size());

	worldRenderer.GetVertexBuffer().push_back(device.CreateVertexBuffer
	({
		cylinderVertices.data(),				
		static_cast<UINT>(cylinderVertices.size()),
		sizeof(Vertex)
	}));

	worldRenderer.GetIndexBuffer().push_back(device.CreateIndexBuffer
	({
		cylinderIndices.data(),
		static_cast<UINT>(cylinderIndices.size())
	}));

	m_cylinderComponent = CreateOrGetComponent<CylinderComponent>();
}

void szas::Cylinder::OnCreate()
{

}

void szas::Cylinder::OnUpdate(f32 deltaTime)
{

}

szas::Cylinder::~Cylinder()
{

}
