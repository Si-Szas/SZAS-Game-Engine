#pragma once
#include <SZAS/Core/Core.h>

namespace szas
{
	class Vec4
	{
		public:
			//CONSTRUCTOR
			Vec4() = default;
			Vec4(f32 x, f32 y, f32 z, f32 w) : x(x), y(y), z(z), w(w)
			{
			}

		public:
			f32 x{}, y{}, z{}, w{};
	};
}