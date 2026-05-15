#include <SZAS/Graphics/GraphicsEngine.h>
#include <SZAS/Graphics/RenderSystem.h>

szas::GraphicsEngine::GraphicsEngine(const GraphicsEngineDescriptor& descriptor) : Base(descriptor.base)
{
	m_renderSystem = std::make_shared<RenderSystem>(RenderSystemDescriptor{ m_logger });
}

szas::RenderSystem& szas::GraphicsEngine::getRenderSystem() const noexcept
{
	//Using * on a unique pointer gives us a non null reference
	return *m_renderSystem;
}

szas::GraphicsEngine::~GraphicsEngine()
{
}
