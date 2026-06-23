#pragma once
#include <SZAS/Core/Core.h>
#include <SZAS/Core/Common.h>
#include <SZAS/Core/Base.h>
#include <SZAS/Core/Identifier.h>

#include <SZAS/Game/WorldRenderer.h>
#include <SZAS/AGameObject/Cube.h>

#include <unordered_map>
#include <vector>
#include <span>

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

				AGameObjectDescriptor descriptor{
					.base = {m_logger},
					.gameContext = m_gameContext,
					.world = *this,
					.worldRenderer = m_worldRenderer
				};

				std::unique_ptr<Type> typedPointer = std::make_unique<Type>(descriptor);

				UniquePtr<AGameObject> gameObjEvent = std::move(typedPointer);

				return static_cast<Type*>(CreateAGameObjectInternal(gameObjEvent));

				//UniquePtr<AGameObject> gameObjEvent = std::make_unique<Type>(AGameObjectDescriptor
				//	{
				//		{m_logger},
				//		m_gameContext,
				//		*this,
				//		*m_worldRenderer
				//	});
				//
				//return static_cast<Type*>(CreateAGameObjectInternal(gameObjEvent));
			}

			template <typename Type>
			Type* const* GetAGameObject(ui32& numberOfComponents) const noexcept
			{
				return reinterpret_cast<Type* const*>(GetAGameObjectsInternal(Type::getTypeId(), &numberOfComponents));
			}

			template <typename Type>
			Type* const* GetAComponent(ui32& numberOfComponents) const noexcept
			{
				return reinterpret_cast<Type* const*>(CreateAComponentsInternal(Type::getTypeId(), &numberOfComponents));
			}

			AGameObject* CreateAGameObjectInternal(UniquePtr<AGameObject>& object);
			AComponent* const* CreateAComponentsInternal(size_t typeID, ui32* numberOfComponents) const noexcept;

			std::span<szas::AGameObject* const> GetAllGameObjects() const noexcept;
			AGameObject* const* GetAGameObjectsInternal(size_t typeID, ui32* numberOfObjects) const noexcept;
			
			void AddComponentInternal(AComponent& component);
			void AddDirtyTransformInternal(TransformComponent& transformComponent);

			void DestroyAGameObject(AGameObject* object);
			void DeleteAllAGameObjects();
			void DestroyAGameObjectInternal(AGameObject* object);
			void DestroyAllAGameObjectsInternal();

			void Update(f32 deltaTime);

		private:
			enum class EventType
			{
				Create = 0,
				Destroy,
				DestroyAll
			};

			struct AGameObjectEvent
			{
				AGameObject* object{};
				size_t pendingObjectIndex{};
				EventType eventType{};
			};

			std::vector<AGameObject*> m_allObjects{};

			std::unordered_map<size_t, std::vector<UniquePtr<AGameObject>>> m_objects{};
			std::unordered_map<size_t, std::vector<AComponent*>> m_components{};

			std::vector<TransformComponent*> m_dirtyTransforms{};

			std::vector<UniquePtr<AGameObject>> m_pendingObjects;
			std::vector<UniquePtr<AGameObject>> m_pendingObjectsSwapBuffer;

			std::vector<AGameObjectEvent> m_events{};
			std::vector<AGameObjectEvent> m_eventsSwapBuffer{};

			GameContext m_gameContext;
			WorldRenderer& m_worldRenderer;

		friend class AGameObject;
		friend class Cube;
		friend class Sphere;

		friend class AComponent;
	};
}