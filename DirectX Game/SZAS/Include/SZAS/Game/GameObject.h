#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/Core/Identifier.h>

namespace szas
{
	class GameObject : public Identifier
	{
		szas_typeid(GameObject)

		//CONSTRUCTOR
		public:
			explicit GameObject(const GameObjectDescriptor& descriptor);

		protected:
			virtual void OnCreate() 
			{
			}
			virtual void OnUpdate(f32 deltaTime) 
			{
			}

		private:
			size_t GetWorldIndex() const noexcept;
			void SetWorldIndex(size_t index) noexcept;

		private:
			World& m_world;
			size_t m_worldIndex{};

		friend class World;
	};
}
