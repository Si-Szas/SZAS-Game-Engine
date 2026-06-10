#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/AComponent/AComponent.h>
#include <SZAS/AComponent/TransformComponent.h>
#include <SZAS/Game/World.h>

szas::AGameObject::AGameObject(const AGameObjectDescriptor& descriptor) :
	Identifier(descriptor.base),
	m_world(descriptor.world)
{
	CreateOrGetComponent<TransformComponent>();
}

szas::AGameObject::~AGameObject()
{
}

szas::AComponent* szas::AGameObject::CreateComponentInternal(UniquePtr<AComponent>& component)
{
	if (component)
	{
		auto typeID = component->GetTypeID();
		auto pointer = component.get();

		if (m_components.find(typeID) != m_components.end()) return {};
		
		m_components.emplace(typeID, std::move(component));
		m_world.AddComponentInternal(*pointer);
	}

	return {};
}

szas::AComponent* szas::AGameObject::GetComponentInternal(size_t ID)
{
	auto it = m_components.find(ID);
	
	if (it != m_components.end()) return it->second.get();
	
	return {};
}

//size_t szas::AGameObject::GetWorldIndex() const noexcept
//{
//	return m_worldIndex;
//}
//
//void szas::AGameObject::SetWorldIndex(size_t index) noexcept
//{
//	m_worldIndex = index;
//}
