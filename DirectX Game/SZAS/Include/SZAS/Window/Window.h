#pragma once
#include <SZAS/Core/Base.h>
#include <SZAS/Core/Common.h>

namespace szas
{
	//Follows RAII. Resources acquired during initialization and released during destruction.
	class Window : public Base
	{
		public:
			//CONSTRUCTOR
			explicit Window(const WindowDescriptor& descriptor);
			//DESTRUCTOR
			virtual ~Window() override;

		protected:
			void* m_handle{}; //Void pointer to not expose public header files
			Rect m_size{};
	};
}