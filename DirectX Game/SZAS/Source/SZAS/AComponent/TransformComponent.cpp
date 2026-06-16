#include <SZAS/AComponent/TransformComponent.h>
#include <SZAS/Game/World.h>

using namespace szas;

szas::TransformComponent::TransformComponent(const AComponentDescriptor& descriptor) :
	AComponent(descriptor)
{
	MarkAsDirty();
}

void szas::TransformComponent::SetPosition(const Vec3& position)
{
	m_position = position;
	MarkAsDirty();
}

Vec3 szas::TransformComponent::GetPosition() const noexcept
{
	return m_position;
}

void szas::TransformComponent::SetScale(const Vec3& scale)
{
	m_scale = scale;
	MarkAsDirty();
}

Vec3 szas::TransformComponent::GetScale() const noexcept
{
	return m_scale;
}

void szas::TransformComponent::SetRotation(const Vec3& rotation)
{
	m_rotation = rotation;
	MarkAsDirty();
}

Vec3 szas::TransformComponent::GetRotation() const noexcept
{
	return m_rotation;
}

Vec3 szas::TransformComponent::Forward()
{
	auto forward = GetRigidWorldMatrix().Row(2);
	return szas::Vec3::normalize({ forward.x, forward.y, forward.z });
}

Vec3 szas::TransformComponent::Right()
{
	auto right = GetRigidWorldMatrix().Row(0);
	return szas::Vec3::normalize({ right.x, right.y, right.z });
}

Vec3 szas::TransformComponent::Up()
{
	auto up = GetRigidWorldMatrix().Row(1);
	return szas::Vec3::normalize({ up.x, up.y, up.z });
}

void szas::TransformComponent::UpdateWorldMatrix() noexcept
{
	//If the transform component is not marked to be updated, then return
	if (m_isDirty)
	{
		m_isDirty = false;

		m_rigidWorldMatrix =
			//Concerned only about rotation and translate
			Matrix4x4::RotateAlongX(m_rotation.x) *
			Matrix4x4::RotateAlongY(m_rotation.y) *
			Matrix4x4::RotateAlongZ(m_rotation.z) *

			//Then translate
			Matrix4x4::Translate(m_position);

		m_affineWorldMatrix =
			Matrix4x4::Scale(m_scale) * m_rigidWorldMatrix;
	}
}

Matrix4x4 szas::TransformComponent::GetAffineWorldMatrix() noexcept
{
	UpdateWorldMatrix();
	return m_affineWorldMatrix;
}

Matrix4x4 szas::TransformComponent::GetRigidWorldMatrix() noexcept
{
	UpdateWorldMatrix();
	return m_rigidWorldMatrix;
}

void szas::TransformComponent::MarkAsDirty()
{
	//If its already marked as dirty, then return
	if (!m_isDirty)
	{
		m_isDirty = true;
		m_world.AddDirtyTransformInternal(*this);
	}
}
