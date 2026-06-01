#pragma once
#include <SZAS/Core/Core.h>
#include <SZAS/Core/Base.h>
#include <SZAS/Math/Vec3.h>
#include <SZAS/Math/Vec4.h>
#include <SZAS/Math/Mat4x4.h>

namespace szas
{
	//We don't want the graphics engine to be further dervied by other classes
	class GraphicsEngine final: public Base
	{
		public:
			//CONSTRUCTOR
			explicit GraphicsEngine(const GraphicsEngineDescriptor& descriptor);

			//GETTER
				GraphicsDevice& GetGraphicsDevice() noexcept;
			
			//RENDER
			void Render(SwapChain& swapChain); //Important for rendering objects to the screen (app window)

			//DESTRUCTOR
			virtual ~GraphicsEngine() override;

		private:
			struct Vertex 
			{
				Vec3 position;
				//Vec3 position1;
				Vec4 color;
				//Vec4 color1;
			};

			//prevent adding variables
			//struct alignas(16) ConstantData
			//{
			//	unsigned int m_time;
			//};

			struct alignas(16) ConstantData
			{
				Mat4x4 world{};
			};

		private:
			//Define a smart pointer to a render system variable of class Render System
			std::shared_ptr<GraphicsDevice> m_graphicsDevice{};
			DeviceContextPtr m_deviceContext{};
			GraphicsPipelineStatePtr m_pipeline{};
			VertexBufferPtr m_vertexBuffer{};
			ConstantBufferPtr m_constantBuffer{};

			//Testing Matrix
			f32 m_rotation{}, m_scale{}, m_position{-1.0f};
	};
}

