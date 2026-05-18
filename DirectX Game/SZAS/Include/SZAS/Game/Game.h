#pragma once
#include <SZAS/Core/Base.h>
#include <SZAS/Core/Core.h>

namespace szas
{
	class Game : public Base
	{
		public:
			//CONSTRUCTOR
			explicit Game(const GameDescriptor& descriptor);

			//FUNCTIONS
				//final is used to indicate that run cannot be further overwritten or inherited
			virtual void Run() final;

			//DESTRUCTOR
			virtual ~Game() override;

		private:
			void OnInternalUpdate(); //Act as a callback where we can place all the code that we need to execute each frame

		private:
			std::unique_ptr<Logger> m_loggerPtr{};
			//Last defined attirbute is first to be allocated, so we want our window to be first
			std::unique_ptr<GraphicsEngine> m_graphicsEngine{};
			//Using smart pointers avoid memory leaks in case a pointer is not deleted
			std::unique_ptr <Display> m_display{};
			//Game loop is running
			bool m_isRunning{ true };
	};
}

