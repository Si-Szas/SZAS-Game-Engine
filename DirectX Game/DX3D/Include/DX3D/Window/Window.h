#pragma once
#include <DX3D/Core/Base.h>

namespace dx3d
{
	//Follows RAII. Resources acquired during initialization and released during destruction.
	class Window : public Base
	{
		public:
			//CONSTRUCTOR
			Window();
			//DESTRUCTOR
			virtual ~Window() override;

		private:
			void* m_handle{}; //Void pointer to not expose public header files
	};
}