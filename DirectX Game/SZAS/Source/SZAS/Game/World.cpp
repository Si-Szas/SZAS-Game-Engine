#include <SZAS/Game/World.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/AComponent/AComponent.h>
#include <SZAS/AComponent/TransformComponent.h>

szas::World::World(const WorldDescriptor& descriptor) : Base(descriptor.base)
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

		auto index = m_pendingObjects.size();

		m_pendingObjects.push_back(std::move(object));
		m_events.push_back({ pointer, index, EventType::Create });

		return pointer;
	}

	return {};
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

