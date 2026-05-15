#pragma once
#include <SZAS/Core/Core.h>

namespace szas
{
	class Rect
	{
		public:
			//Parameterless constructor with an empty body
			Rect() = default;
			Rect(i32 width, i32 height) : left(0), top(0), width(width), height(height) {}
			Rect(i32 left, i32 top, i32 width, i32 height) : left(left), top(top), width(width), height(height) {}
		public:
			i32 left{}, top{}, width{}, height{};
	};
}