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
			T* CreateAGameObject()
			{
				static_assert(std::is_base_of<AGameObject, T>::value, "T must inherit from szas::AGameObject.");
				static_assert(HasTypeID<T>, "T needs a unique TypeID. Make sure you have added szas_typeid and applied it to the correct class.");

				UniquePtr<AGameObject> gameObjEvent = std::make_unique<T>(AGameObjectDescriptor
					{
						{m_logger},
						*this
					});

				return static_cast<T*>(CreateAGameObjectInternal(gameObjEvent));
			}

			void Update(f32 deltaTime);

			AGameObject* CreateAGameObjectInternal(UniquePtr<AGameObject>& object);

		private:
			enum class EventType
			{
				Create = 0
			};

			struct AGameObjectEvent
			{
				AGameObject* object{};
				EventType eventType{};
			};

			std::unordered_map<size_t, std::vector<UniquePtr<AGameObject>>> m_objects;
			
			std::vector<UniquePtr<AGameObject>> m_pendingObjects;
			std::vector<UniquePtr<AGameObject>> m_pendingObjectsSwapBuffer;

			std::vector<AGameObjectEvent> m_events{};
			std::vector<AGameObjectEvent> m_eventsSwapBuffer{};
	};
}