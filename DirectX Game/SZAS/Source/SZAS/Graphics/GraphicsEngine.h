#pragma once
#include <SZAS/Core/Core.h>
#include <SZAS/Core/Base.h>
#include <SZAS/Math/Vec3.h>
#include <SZAS/Math/Vec4.h>
#include <SZAS/Math/Matrix4x4.h>
//#include <SZAS/Graphics/AGameObject/AGameObject.h>
#include <SZAS/Graphics/AGameObject/Quad/Quad.h>
#include <vector>

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

			//private:
			//	struct Vertex
			//	{
			//		Vec3 position;
			//		Vec4 color;
			//	};
			//
			struct alignas(16) ConstantData
			{
				Matrix4x4 world{};
				//Matrix4x4 view{};
				Matrix4x4 projection{};
			};

		private:
			//Define a smart pointer to a render system variable of class Render System
			RefPtr<GraphicsDevice> m_graphicsDevice{};
			RefPtr<DeviceContext> m_deviceContext{};
			RefPtr<GraphicsPipelineState> m_pipeline{};
			RefPtr<VertexBuffer> m_vertexBuffer{};
			RefPtr<ConstantBuffer> m_vsConstantBuffer{};
			RefPtr<ConstantBuffer> m_psConstantBuffer{};
			RefPtr<IndexBuffer> m_indexBuffer{};
			//RefPtr<AGameObject> m_AGameObject{};
			
			//List of Quads
			//std::vector<Quad*> m_quadList{};

			//Testing Matrix Transformation
			f32 m_rotation{}, m_scale{1.0f}, m_position{0.0f};
	};
}

