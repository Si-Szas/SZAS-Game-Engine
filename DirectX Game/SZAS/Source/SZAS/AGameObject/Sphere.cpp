#include <SZAS/AGameObject/Sphere.h>

szas::Sphere::Sphere(const AGameObjectDescriptor& descriptor) :
	AGameObject(descriptor)
{
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
