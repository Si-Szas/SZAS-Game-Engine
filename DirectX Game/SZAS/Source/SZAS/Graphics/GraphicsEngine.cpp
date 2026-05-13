#include <SZAS/Graphics/GraphicsEngine.h>
#include <SZAS/Graphics/RenderSystem.h>

szas::GraphicsEngine::GraphicsEngine(const GraphicsEngineDescriptor& descriptor) : Base(descriptor.base)
{
	m_renderSystem = std::make_unique<RenderSystem>(RenderSystemDescriptor{ m_logger });
}

szas::GraphicsEngine::~GraphicsEngine()
{
}
