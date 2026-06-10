#include <SZAS/AGameObject/AGameObject.h>

szas::AGameObject::AGameObject(const AGameObjectDescriptor& descriptor) :
	Identifier(descriptor.base),
	m_world(descriptor.world)
{
}

szas::AGameObject::~AGameObject()
{
}

size_t szas::AGameObject::GetWorldIndex() const noexcept
{
	return m_worldIndex;
}

void szas::AGameObject::SetWorldIndex(size_t index) noexcept
{
	m_worldIndex = index;
}
