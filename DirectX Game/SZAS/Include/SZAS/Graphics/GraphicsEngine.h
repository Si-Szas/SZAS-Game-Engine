#pragma once
#include <SZAS/Core/Core.h>
#include <SZAS/Core/Base.h>

namespace szas
{
	//We don't want the graphics engine to be further dervied by other classes
	class GraphicsEngine final: public Base
	{
		public:
			//CONSTRUCTOR
			explicit GraphicsEngine(const GraphicsEngineDescriptor& descriptor);

			//DESTRUCTOR
			virtual ~GraphicsEngine() override;

		private:
			//Define a smart pointer to a render system variable of class Render System
			std::unique_ptr<RenderSystem> m_renderSystem{};
	};
}

