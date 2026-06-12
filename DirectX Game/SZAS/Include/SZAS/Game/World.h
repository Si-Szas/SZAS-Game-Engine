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

			//FUNCTIONS
			template <typename Type>
			Type* CreateAGameObject() requires IsRegistered<AGameObject, Type>
			{
				static_assert(std::is_base_of<AGameObject, Type>::value, "Type must inherit from szas::AGameObject.");
				static_assert(HasTypeID<Type>, "Type needs a unique TypeID. Make sure you have added szas_typeid and applied it to the correct class.");

				UniquePtr<AGameObject> gameObjEvent = std::make_unique<Type>(AGameObjectDescriptor
					{
						{m_logger},
						*this
					});

				return static_cast<Type*>(CreateAGameObjectInternal(gameObjEvent));
			}

			template <typename Type>
			Type* const* GetAComponents(ui32& numberOfComponents) const noexcept
			{
				return reinterpret_cast<Type* const*>(CreateAComponentsInternal(Type::getTypeId(), &numberOfComponents));
			}

			AGameObject* CreateAGameObjectInternal(UniquePtr<AGameObject>& object);
			AComponent* const* CreateAComponentsInternal(size_t typeID, ui32* numberOfComponents) const noexcept;

			void AddComponentInternal(AComponent& component);
			void AddDirtyTransformInternal(TransformComponent& transformComponent);

			void Update(f32 deltaTime);

		private:
			enum class EventType
			{
				Create = 0
			};

			struct AGameObjectEvent
			{
				AGameObject* object{};
				size_t pendingObjectIndex{};
				EventType eventType{};
			};

			std::unordered_map<size_t, std::vector<UniquePtr<AGameObject>>> m_objects{};
			std::unordered_map<size_t, std::vector<AComponent*>> m_components{};

			std::vector<TransformComponent*> m_dirtyTransforms{};

			std::vector<UniquePtr<AGameObject>> m_pendingObjects;
			std::vector<UniquePtr<AGameObject>> m_pendingObjectsSwapBuffer;

			std::vector<AGameObjectEvent> m_events{};
			std::vector<AGameObjectEvent> m_eventsSwapBuffer{};

		friend class AGameObject;
		friend class AComponent;
	};
}