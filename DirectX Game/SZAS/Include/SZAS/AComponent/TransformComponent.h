#pragma once
#include <SZAS/Core/Core.h>
#include <SZAS/AComponent/AComponent.h>
#include <SZAS/Math/Vec3.h>
#include <SZAS/Math/Matrix4x4.h>

namespace szas
{
	class TransformComponent final : public AComponent
	{
		szas_typeid(TransformComponent)

		public:
			//CONSTRUCTOR
			explicit TransformComponent(const AComponentDescriptor& descriptor);

			//GETTERS & SETTERS
			void SetPosition(const Vec3& position);
			Vec3 GetPosition() const noexcept;

			void SetScale(const Vec3& scale);
			Vec3 GetScale() const noexcept;

			void SetRotation(const Vec3& rotation);
			Vec3 GetRotation() const noexcept;

			void UpdateWorldMatrix() noexcept;

		private:
			//We mark components as "dirty" when it needs to be updated
			void MarkAsDirty();

		private:
			Vec3 m_position{ 0.0f, 0.0f, 0.0f };
			Vec3 m_scale{ 1.0f, 1.0f, 1.0f };
			Vec3 m_rotation{ 0.0f, 0.0f, 0.0f };

			Matrix4x4 m_worldMatrix{};

			bool m_isDirty{};
	};
}

