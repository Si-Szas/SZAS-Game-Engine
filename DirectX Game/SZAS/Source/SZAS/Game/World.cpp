#include <SZAS/Game/World.h>
#include <SZAS/Game/GameObject.h>

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
			auto pendingObjectIndex = gameObjEvent.object->GetWorldIndex();

			if (gameObjEvent.eventType == EventType::Create)
			{
				auto& obj = m_pendingObjectsSwapBuffer[pendingObjectIndex];
				auto ptr = obj.get();

				auto index = m_objects[objectTypeID].size();
				ptr->SetWorldIndex(index);

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

}

szas::GameObject* szas::World::CreateGameObjectInternal(UniquePtr<szas::GameObject>& object)
{
	if (!object) return {};

	auto pointer = object.get();

	auto index = m_pendingObjects.size();
	pointer->SetWorldIndex(index);

	m_pendingObjects.push_back(std::move(object));
	m_events.push_back({ pointer, EventType::Create });

	return pointer;
}