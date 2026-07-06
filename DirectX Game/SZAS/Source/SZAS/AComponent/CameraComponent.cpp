#include <SZAS/AComponent/CameraComponent.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/AComponent/TransformComponent.h>

szas::CameraComponent::CameraComponent(const AComponentDescriptor& descriptor) :
	AComponent(descriptor)
{
	ComputeProjectionMatrix();
}

szas::Matrix4x4 szas::CameraComponent::GetViewMatrix() noexcept
{
	return Matrix4x4::Inverse(m_object.GetTransform().GetRigidWorldMatrix());
}

szas::Matrix4x4 szas::CameraComponent::GetProjectionMatrix() const noexcept
{
	return m_projection;
}

void szas::CameraComponent::SetFarPlane(f32 farPlane) noexcept
{
	if (farPlane <= m_nearPlane) return;
	m_farPlane = farPlane;
	ComputeProjectionMatrix();
}

szas::f32 szas::CameraComponent::GetFarPlane() const noexcept
{
	return m_farPlane;
}

void szas::CameraComponent::SetNearPlane(f32 nearPlane) noexcept
{
	if (nearPlane <= 0.001f) return;
	m_nearPlane = nearPlane;
	ComputeProjectionMatrix();
}

szas::f32 szas::CameraComponent::GetNearPlane() const noexcept
{
	return m_nearPlane;
}

void szas::CameraComponent::SetFieldOfView(f32 fieldOfView) noexcept
{
	if (fieldOfView <= 0.001f || fieldOfView >= MathUtility::PI) return;
	m_fieldOfView = fieldOfView;
	ComputeProjectionMatrix();
}

szas::f32 szas::CameraComponent::GetFieldOfView() const noexcept
{
	return m_fieldOfView;
}

void szas::CameraComponent::SetViewportSize(const Rect& size) noexcept
{
	if (m_viewportSize == size) return;
	if (m_viewportSize.width == 0 || m_viewportSize.height == 0) return;

	m_viewportSize = size;
	ComputeProjectionMatrix();
}

szas::Rect szas::CameraComponent::GetViewportSize() const noexcept
{
	return m_viewportSize;
}

void szas::CameraComponent::ComputeProjectionMatrix() noexcept
{
	m_projection = 
		Matrix4x4::PerspectiveFOVLH
		(
			m_fieldOfView, 
			(f32)m_viewportSize.width / (f32)m_viewportSize.height,
			m_nearPlane, m_farPlane
		);
}

