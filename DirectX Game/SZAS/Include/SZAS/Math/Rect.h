#pragma once
#include <SZAS/Core/Core.h>

namespace szas
{
	class Rect
	{
		public:
			//Parameterless constructor with an empty body
			Rect() = default;
			Rect(i32 _width, i32 _height) : left(0), top(0), width(_width), height(_height) {}
			Rect(i32 _left, i32 _top, i32 _width, i32 _height) : left(_left), top(_top), width(_width), height(_height) {}
		public:
			i32 left{}, top{}, width{}, height{};
	};
}