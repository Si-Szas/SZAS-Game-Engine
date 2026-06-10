#include <SZAS/Game/GameObject.h>

szas::GameObject::GameObject(const GameObjectDescriptor& descriptor) :
	Identifier(descriptor.base),
	m_world(descriptor.world)
{
}

size_t szas::GameObject::GetWorldIndex() const noexcept
{
	return m_worldIndex;
}

void szas::GameObject::SetWorldIndex(size_t index) noexcept
{
	m_worldIndex = index;
}
