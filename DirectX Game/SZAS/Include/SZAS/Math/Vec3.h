#pragma once
#include <SZAS/Core/Core.h>

namespace szas
{
	class Vec3
	{
	public:
		//CONSTRUCTOR
		Vec3() = default;
		Vec3(f32 all) : x(all), y(all), z(all)
		{
		}
		Vec3(f32 _x, f32 _y, f32 _z) : x(_x), y(_y), z(_z)
		{
		}

		Vec3 operator+=(const Vec3& rightHandSide) 
		{
			x += rightHandSide.x;
			y += rightHandSide.y;
			z += rightHandSide.z;

			return *this;
		}

		Vec3 operator*=(const Vec3 & rightHandSide) 
		{
			x *= rightHandSide.x;
			y *= rightHandSide.y;
			z *= rightHandSide.z;

			return *this;
		}

		static Vec3 normalize(const Vec3& vector)
		{
			float lengthSquared = 
				vector.x * vector.x + 
				vector.y * vector.y + 
				vector.z * vector.z;

			if (lengthSquared == 0) return Vec3{ 0.0f };

			float inverseLength = 1.0f / std::sqrt(lengthSquared);

			return Vec3
			{
				vector.x * inverseLength,
				vector.y * inverseLength,
				vector.z * inverseLength
			};
		}

		friend Vec3 operator+(Vec3 leftHandSide, const Vec3& rightHandSide)
		{
			leftHandSide += rightHandSide;
			return leftHandSide;
		}

		friend Vec3 operator*(Vec3 vector, f32 scalar)
		{
			vector *= scalar;
			return vector;
		}

		friend Vec3 operator*(f32 scalar, Vec3 vector)
		{
			vector *= scalar;
			return vector;
		}

	public:
		f32 x{}, y{}, z{};
	};
}
