#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/Core/Identifier.h>
#include <SZAS/AComponent/AComponent.h>
#include <unordered_map>

namespace szas
{
	class AGameObject : public Identifier
	{
		szas_typeid(AGameObject)

		public:
			//CONSTRUCTOR
			explicit AGameObject(const AGameObjectDescriptor& descriptor);

			template <typename Type>
			Type* CreateOrGetComponent() requires IsRegistered<AComponent, Type>
			{
				auto comp = GetComponent<Type>();
				if (comp) return comp;
				UniquePtr<AComponent> component = std::make_unique<Type>(AComponentDescriptor{
					{m_logger},
					*this,
					m_world
				});
				return static_cast<Type*>(CreateComponentInternal(component));
			}

			template <typename Type>
			Type* GetComponent() requires IsRegistered<AComponent, Type>
			{
				return static_cast<Type*>(GetComponentInternal(Type::getTypeId()));
			}

			//Get offset
			ui32 GetVertexOffset() noexcept;
			ui32 GetIndexLocation() noexcept;

			//Get the transform component
			TransformComponent& GetTransform() noexcept;
			World& GetWorld() noexcept;
			InputSystem& GetInputSystem() noexcept;
			const WorldRenderer& GetWorldRenderer() noexcept;

			//DESTRUCTOR
			virtual ~AGameObject();

		protected:
			virtual void OnCreate() 
			{
			}
			virtual void OnUpdate(f32 deltaTime) 
			{
			}

		private:
			AComponent* CreateComponentInternal(UniquePtr<AComponent>& component);
			AComponent* GetComponentInternal(size_t ID);

		private:
			std::unordered_map<size_t, UniquePtr<AComponent>> m_components{};
			
			// COMPONENTS SHARED BY ALL GAME OBJECTS
			TransformComponent* m_transform{};
			GameContext m_gameContext;
			World& m_world;
			const WorldRenderer& m_worldRenderer;

		protected:
			// COUNTERS
			ui32 m_vertexOffset = 0;
			ui32 m_indexLocation = 0;

		friend class World;
	};
}
