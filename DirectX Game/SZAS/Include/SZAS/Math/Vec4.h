#pragma once
#include <SZAS/Core/Core.h>

namespace szas
{
	class Vec4
	{
		public:
			//CONSTRUCTOR
			Vec4() = default;
			Vec4(f32 _x, f32 _y, f32 _z, f32 _w) : x(_x), y(_y), z(_z), w(_w)
			{
			}

		public:
			f32 x{}, y{}, z{}, w{};
	};
}