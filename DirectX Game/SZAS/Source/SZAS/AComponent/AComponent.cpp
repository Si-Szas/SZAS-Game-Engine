#include <SZAS/AComponent/AComponent.h>

szas::AComponent::AComponent(const AComponentDescriptor& descriptor) :
	Identifier(descriptor.base),
	m_object(descriptor.object),
	m_world(descriptor.world)
{
}

szas::AGameObject& szas::AComponent::GetGameObject() noexcept
{
	return m_object;
}
