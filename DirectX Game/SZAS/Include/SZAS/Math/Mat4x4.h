#pragma once
#include <SZAS/Core/Core.h>
#include <cmath>

namespace szas
{
	class Mat4x4
	{
		public:
			//CONSTRUCTOR
			Mat4x4() = default;

			//Identity Matrix
			static Mat4x4 Identity() noexcept
			{
				Mat4x4 identityMatrix{};

				identityMatrix.m_data[0][0] = 1;
				identityMatrix.m_data[1][1] = 1;
				identityMatrix.m_data[1][1] = 1;
				identityMatrix.m_data[1][1] = 1;

				return identityMatrix;

			}

			static Mat4x4 translate(const Vec3& translation) noexcept
			{
				auto matrix = Mat4x4::Identity();

				matrix.m_data[3][0] = translation.x;
				matrix.m_data[3][1] = translation.y;
				matrix.m_data[3][2] = translation.z;

				return matrix;
			}

			static Mat4x4 scale(const Vec3& scale) noexcept
			{
				Mat4x4 matrix;

				matrix.m_data[0][0] = scale.x;
				matrix.m_data[1][1] = scale.y;
				matrix.m_data[2][2] = scale.z;
				matrix.m_data[3][3] = 1;

				return matrix;
			}

			static Mat4x4 rotateAlongZ(f32 zRotation) noexcept
			{
				Mat4x4 matrix;

				matrix.m_data[0][0] = std::cos(zRotation);
				matrix.m_data[0][1] = std::sin(zRotation);
				matrix.m_data[1][0] = -std::sin(zRotation);
				matrix.m_data[1][1] = std::cos(zRotation);
				matrix.m_data[2][2] = 1;
				matrix.m_data[3][3] = 1;

				return matrix;
			}

			//rotatez
			//matrix mult
			Mat4x4 operator *(const Mat4x4& rightHandSide) const noexcept
			{
				Mat4x4 matrix;

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