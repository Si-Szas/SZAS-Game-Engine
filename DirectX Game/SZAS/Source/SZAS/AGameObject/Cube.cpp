#include <SZAS/AGameObject/Cube.h>

szas::Cube::Cube(const AGameObjectDescriptor& descriptor) :
	AGameObject(descriptor)
{
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
