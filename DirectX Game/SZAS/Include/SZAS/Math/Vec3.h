#pragma once
#include <SZAS/Core/Core.h>

namespace szas
{
	class Vec3
	{
	public:
		//CONSTRUCTOR
		Vec3() = default;
		Vec3(f32 _x, f32 _y, f32 _z) : x(_x), y(_y), z(_z)
		{
		}

	public:
		f32 x{}, y{}, z{};
	};
}