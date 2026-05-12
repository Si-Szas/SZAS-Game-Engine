#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Core.h>

namespace dx3d{
	class Game : public Base
	{
		public:
			//CONSTRUCTOR
			Game();

			//FUNCTIONS
				//final is used to indicate that run cannot be further overwritten or inherited
			virtual void run() final;

			//DESTRUCTOR
			virtual ~Game() override;

		private:
			//Using smart pointers avoid memory leaks in case a pointer is not deleted
			std::unique_ptr <Window> m_display{};
			//Game loop is running
			bool m_isRunning{ true };
	};
}

