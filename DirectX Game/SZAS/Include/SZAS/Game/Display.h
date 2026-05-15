#pragma once
#include <SZAS/Window/Window.h>

namespace szas
{
	class Display final : public Window
	{
		public:
			//CONSTRUCTOR
			explicit Display(const DisplayDescriptor& descriptor);

		private:
			SwapChainPtr m_swapChain{};
	};
}
