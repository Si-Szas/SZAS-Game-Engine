#include <SZAS/Game/World.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/AComponent/AComponent.h>
#include <SZAS/AComponent/TransformComponent.h>

#include <span>

szas::World::World(const WorldDescriptor& descriptor) : Base(descriptor.base),
	m_gameContext(descriptor.gameContext)
{

}

void szas::World::Update(f32 deltaTime)
{
	if (m_events.size())
	{
		std::swap(m_events, m_eventsSwapBuffer);
		std::swap(m_pendingObjects, m_pendingObjectsSwapBuffer);

		for (auto& gameObjEvent : m_eventsSwapBuffer)
		{
			auto objectTypeID = gameObjEvent.object->GetTypeID();
			auto pendingObjectIndex = gameObjEvent.pendingObjectIndex;

			if (gameObjEvent.eventType == EventType::Create)
			{
				auto& obj = m_pendingObjectsSwapBuffer[pendingObjectIndex];
				auto ptr = obj.get();

				m_objects[objectTypeID].push_back(std::move(obj));

				ptr->OnCreate();
			}
		}

		m_pendingObjectsSwapBuffer.clear();
		m_eventsSwapBuffer.clear();
	}

	for (auto&& [typeID, objects] : m_objects)
	{
		for (auto& object : objects)
		{
			object->OnUpdate(deltaTime);
		}
	}

	//Update the transform components if they were marked as "dirty"
	for (auto& component : m_dirtyTransforms)
	{
		component->UpdateWorldMatrix();
	}

	//Clear the list of dirty component to ensure that they don't get included in next update
	m_dirtyTransforms.clear();

}

szas::AGameObject* szas::World::CreateAGameObjectInternal(UniquePtr<szas::AGameObject>& object)
{
	if (object) 
	{

		auto pointer = object.get();

		size_t typeID = pointer->getTypeId();

		m_allObjects.push_back(pointer);

		auto index = m_pendingObjects.size();

		m_pendingObjects.push_back(std::move(object));
		m_events.push_back({ pointer, index, EventType::Create });

		return pointer;
	}

	return {};
}

szas::AComponent* const* szas::World::CreateAComponentsInternal(size_t typeID, ui32* numberOfComponents) const noexcept
{
	auto it = m_components.find(typeID);

	if (it != m_components.end())
	{
		*numberOfComponents = static_cast<ui32>(it->second.size());
		return it->second.data();
	}

	*numberOfComponents = 0u;
	return {};
}

szas::AGameObject* const* szas::World::GetAGameObjectsInternal(size_t typeID, ui32* numberOfObjects) const noexcept
{
	auto obj = m_objects.find(typeID);

	if (obj == m_objects.end() || obj->second.empty())
	{
		if (numberOfObjects) *numberOfObjects = 0;
		return nullptr;
	}

	const auto& uniquePtrs = obj->second;
	if (numberOfObjects)
	{
		*numberOfObjects = static_cast<ui32>(uniquePtrs.size());
	}

	return reinterpret_cast<AGameObject* const*>(uniquePtrs.data());
}

void szas::World::AddComponentInternal(AComponent& component)
{
	//Add a component via ID
	auto typeID = component.GetTypeID();
	m_components[typeID].push_back(&component);
}

void szas::World::AddDirtyTransformInternal(TransformComponent& transformComponent)
{
	m_dirtyTransforms.push_back(&transformComponent);
}

std::span<szas::AGameObject* const> szas::World::GetAllGameObjects() const noexcept
{
	return m_allObjects;
}