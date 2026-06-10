#pragma once
#include <SZAS/Core/Core.h>
#include <SZAS/Core/Common.h>
#include <SZAS/Core/Base.h>
#include <SZAS/Core/Identifier.h>
#include <unordered_map>
#include <vector>

namespace szas
{
	class World final : public Base
	{
		public:
			//CONSTRUCTOR
			explicit World(const WorldDescriptor& worldDescriptor);

			template <typename T>
			T* CreateGameObject()
			{
				static_assert(std::is_base_of<GameObject, T>::value, "T must inherit from szas::AGameObject.");
				static_assert(HasTypeID<T>, "T needs a unique TypeID. Make sure you have added szas_typeid and applied it to the correct class.");

				UniquePtr<GameObject> gameObjEvent = std::make_unique<T>(GameObjectDescriptor
					{
						{m_logger},
						*this
					});

				return static_cast<T*>(CreateGameObjectInternal(gameObjEvent));
			}

			void Update(f32 deltaTime);

			GameObject* CreateGameObjectInternal(UniquePtr<GameObject>& object);

		private:
			enum class EventType
			{
				Create = 0
			};

			struct GameObjectEvent
			{
				GameObject* object{};
				EventType eventType{};
			};

			std::unordered_map<size_t, std::vector<UniquePtr<GameObject>>> m_objects;
			
			std::vector<UniquePtr<GameObject>> m_pendingObjects;
			std::vector<UniquePtr<GameObject>> m_pendingObjectsSwapBuffer;

			std::vector<GameObjectEvent> m_events{};
			std::vector<GameObjectEvent> m_eventsSwapBuffer{};
	};
}