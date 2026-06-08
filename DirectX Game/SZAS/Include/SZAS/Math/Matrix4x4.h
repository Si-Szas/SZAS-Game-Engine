#pragma once
#include <SZAS/Core/Core.h>
#include <cmath>
#include <cassert>

namespace szas
{
	class Matrix4x4
	{
		public:
			//CONSTRUCTOR
			Matrix4x4() = default;

			//Identity Matrix
			static Matrix4x4 Identity() noexcept
			{
				Matrix4x4 identityMatrix{};

				identityMatrix.m_data[0][0] = 1;
				identityMatrix.m_data[1][1] = 1;
				identityMatrix.m_data[1][1] = 1;
				identityMatrix.m_data[1][1] = 1;

				return identityMatrix;

			}

			static Matrix4x4 translate(const Vec3& translation) noexcept
			{
				auto matrix = Matrix4x4::Identity();

				matrix.m_data[3][0] = translation.x;
				matrix.m_data[3][1] = translation.y;
				matrix.m_data[3][2] = translation.z;

				return matrix;
			}

			static Matrix4x4 scale(const Vec3& scale) noexcept
			{
				Matrix4x4 matrix{};

				matrix.m_data[0][0] = scale.x;
				matrix.m_data[1][1] = scale.y;
				matrix.m_data[2][2] = scale.z;
				matrix.m_data[3][3] = 1;

				return matrix;
			}

			static Matrix4x4 rotateAlongX(f32 xRotation) noexcept
			{
				Matrix4x4 matrix{};

				matrix.m_data[0][0] = 1;
				matrix.m_data[1][1] = std::cos(xRotation);
				matrix.m_data[2][1] = -std::sin(xRotation);
				matrix.m_data[1][2] = std::sin(xRotation);
				matrix.m_data[2][2] = std::cos(xRotation);
				matrix.m_data[3][3] = 1;

				return matrix;
			}

			static Matrix4x4 rotateAlongY(f32 yRotation) noexcept
			{
				Matrix4x4 matrix{};

				matrix.m_data[0][0] = std::cos(yRotation);
				matrix.m_data[2][0] = std::sin(yRotation);
				matrix.m_data[1][1] = 1;
				matrix.m_data[0][2] = -std::sin(yRotation);
				matrix.m_data[2][2] = std::cos(yRotation);
				matrix.m_data[3][3] = 1;

				return matrix;
			}

			static Matrix4x4 rotateAlongZ(f32 zRotation) noexcept
			{
				Matrix4x4 matrix{};

				matrix.m_data[0][0] = std::cos(zRotation);
				matrix.m_data[0][1] = std::sin(zRotation);
				matrix.m_data[1][0] = -std::sin(zRotation);
				matrix.m_data[1][1] = std::cos(zRotation);
				matrix.m_data[2][2] = 1;
				matrix.m_data[3][3] = 1;

				return matrix;
			}

			static Matrix4x4 orthoLH(f32 width, f32 height, f32 zNear, f32 zFar) noexcept
			{
				assert(width != 0.0f && "OrthoLH: width must not be zero");
				assert(height != 0.0f && "OrthoLH: height must not be zero");
				assert(zFar != zNear && "OrthoLH: zNear and zFar cannot be equal");

				Matrix4x4 matrix{};

				matrix.m_data[0][0] = 2.0f / width;
				matrix.m_data[1][1] = 2.0f / height;
				matrix.m_data[2][2] = 1.0f / (zFar - zNear);
				matrix.m_data[3][2] = -(zNear / (zFar - zNear));
				matrix.m_data[3][3] = 1;

				return matrix;
			}

			Matrix4x4 operator *(const Matrix4x4& rightHandSide) const noexcept
			{
				Matrix4x4 matrix{};

				for (auto row = 0u; row < 4u; row++)
				{
					for (auto i = 0u; i < 4u; i++)
					{
						auto tempMatrix = m_data[row][i];
						for (auto col = 0u; col < 4u; col++)
						{
							matrix.m_data[row][col] += tempMatrix * rightHandSide.m_data[i][col];
						}
					}
				}

				return matrix;
			}

		private:
			f32 m_data[4][4]{};
	};
}