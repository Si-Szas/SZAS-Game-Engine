#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/AComponent/AComponent.h>
#include <SZAS/AComponent/TransformComponent.h>
#include <SZAS/Game/World.h>
#include <SZAS/Game/WorldRenderer.h>

szas::AGameObject::AGameObject(const AGameObjectDescriptor& descriptor) :
	Identifier(descriptor.base),
	m_gameContext(descriptor.gameContext),
	m_world(descriptor.world),
	m_worldRenderer(descriptor.worldRenderer)
{
	m_transform = CreateOrGetComponent<TransformComponent>();
}

szas::AGameObject::~AGameObject()
{
}

szas::AComponent* szas::AGameObject::CreateComponentInternal(UniquePtr<AComponent>& component)
{
	if (component)
	{
		auto typeID = component->GetTypeID();
		auto pointer = component.get();

		if (m_components.find(typeID) != m_components.end()) return {};
		
		m_components.emplace(typeID, std::move(component));
		m_world.AddComponentInternal(*pointer);

		return pointer;
	}

	return {};
}

szas::AComponent* szas::AGameObject::GetComponentInternal(size_t ID)
{
	auto it = m_components.find(ID);
	
	if (it != m_components.end()) return it->second.get();
	
	return {};
}

szas::ui32 szas::AGameObject::GetVertexOffset() noexcept
{
	return m_vertexOffset;
}

void szas::AGameObject::SetVertexOffset(ui32 newOffset) noexcept
{
	m_vertexOffset = newOffset;
}

szas::ui32 szas::AGameObject::GetIndexLocation() noexcept
{
	return m_indexLocation;
}

void szas::AGameObject::SetIndexLocation(ui32 newOffset) noexcept
{
	m_indexLocation = newOffset;
}

szas::TransformComponent& szas::AGameObject::GetTransform() noexcept
{
	return *m_transform;
}

szas::World& szas::AGameObject::GetWorld() noexcept
{
	return m_world;
}

szas::InputSystem& szas::AGameObject::GetInputSystem() noexcept
{
	return m_gameContext.inputSystem;
}

const szas::WorldRenderer& szas::AGameObject::GetWorldRenderer() noexcept
{
	return m_worldRenderer;
}

void szas::AGameObject::ResetMovementModifiers()
{
	forwardModifier = 0.0f;
	rightModifier = 0.0f;
}

szas::Vec3 szas::AGameObject::GetVelocity() const noexcept
{
	return m_velocity;
}

void szas::AGameObject::SetVelocity(Vec3 newVelocity) noexcept
{
	m_velocity = newVelocity;
}

szas::f32 szas::AGameObject::GetForwardModifier() const noexcept
{
	return forwardModifier;
}

void szas::AGameObject::SetForwardModifier(f32 newForward) noexcept
{
	forwardModifier = newForward;
}

szas::f32 szas::AGameObject::GetRightModifier() const noexcept
{
	return rightModifier;
}

void szas::AGameObject::SetRightModifier(f32 newRight) noexcept
{
	rightModifier = newRight;
}

szas::f32 szas::AGameObject::GetSpeedModifier() const noexcept
{
	return speedModifier;
}

void szas::AGameObject::SetSpeedModifier(f32 newSpeed) noexcept
{
	speedModifier = newSpeed;
}

//size_t szas::AGameObject::GetWorldIndex() const noexcept
//{
//	return m_worldIndex;
//}
//
//void szas::AGameObject::SetWorldIndex(size_t index) noexcept
//{
//	m_worldIndex = index;
//}
