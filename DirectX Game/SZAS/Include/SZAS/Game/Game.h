#pragma once
#include <SZAS/Core/Base.h>
#include <SZAS/Core/Core.h>

namespace szas
{
	class Game
	{
		szas_disable_copy_and_move(Game)
		public:
			//CONSTRUCTOR
			explicit Game(const GameDescriptor& descriptor);

			//FUNCTIONS
				//final is used to indicate that run cannot be further overwritten or inherited
			virtual void Run() final;
			
			//GETTER
			virtual World& GetWorld() noexcept final;
			virtual Logger& GetLogger() noexcept final;

			//DESTRUCTOR
			virtual ~Game();

		protected:
			virtual void OnCreate()
			{
			}

			virtual void OnUpdate(f32 deltaTime) 
			{
			} 
			
		private:
			void OnInternalUpdate(f32 deltaTime); //Act as a callback where we can place all the code that we need to execute each frame

		private:
			UniquePtr<Logger> m_logger{};
			//Last defined attirbute is first to be allocated, so we want our window to be first
			UniquePtr<GraphicsEngine> m_graphicsEngine{};
			//Using smart pointers avoid memory leaks in case a pointer is not deleted
			UniquePtr<Display> m_display{};
			//Unique pointer to the world
			UniquePtr<World> m_world{};
			//Game loop is running
			bool m_isRunning{ true };
	};
}

