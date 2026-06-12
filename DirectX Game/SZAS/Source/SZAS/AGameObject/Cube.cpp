#include <SZAS/AGameObject/Cube.h>

szas::Cube::Cube(const AGameObjectDescriptor& descriptor) :
	AGameObject(descriptor)
{
	m_cube = CreateOrGetComponent<CubeComponent>();
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
