#pragma once
#include <SZAS/Core/Core.h>
#include <SZAS/Core/Common.h>
#include <SZAS/Core/Base.h>
#include <SZAS/Math/Vec3.h>
#include <SZAS/Math/Vec4.h>
#include <SZAS/Math/Matrix4x4.h>
#include <vector>

namespace szas
{
	//We don't want the graphics engine to be further dervied by other classes
	class WorldRenderer final: public Base
	{
		public:
			//CONSTRUCTOR
			explicit WorldRenderer(const WorldRendererDescriptor& descriptor);

			//RENDER
			void Render(const World& world, SwapChain& swapChain, f32 deltaTime); //Important for rendering objects to the screen (app window)

			//GETTERS
			GraphicsDevice& GetGraphicsDevice() const noexcept;
			std::vector<RefPtr<VertexBuffer>>& GetVertexBuffer() const noexcept;
			std::vector<RefPtr<IndexBuffer>>& GetIndexBuffer() const noexcept;

			//DESTRUCTOR
			virtual ~WorldRenderer() override;

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
				Matrix4x4 view{};
				Matrix4x4 projection{};
			};

		private:
			//Define a smart pointer to a render system variable of class Render System
			GraphicsDevice& m_graphicsDevice;
			RefPtr<DeviceContext> m_deviceContext{};
			RefPtr<GraphicsPipelineState> m_pipeline{};

			std::vector<RefPtr<VertexBuffer>> m_vertexBuffer{};
			std::vector<RefPtr<IndexBuffer>> m_indexBuffer{};

			RefPtr<ConstantBuffer> m_vsConstantBuffer{};
			RefPtr<ConstantBuffer> m_hsConstantBuffer{};
			RefPtr<ConstantBuffer> m_dsConstantBuffer{};
			RefPtr<ConstantBuffer> m_psConstantBuffer{};
	};
}

