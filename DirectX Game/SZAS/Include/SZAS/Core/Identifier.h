#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/Core/Base.h>

#define szas_typeid(Class) \
public:\
using type_id_tag = Class;\
static size_t getTypeId()\
{\
	static const auto id = typeid(Class).hash_code();\
	return id;\
}\
size_t GetTypeID() const noexcept override\
{\
	return getTypeId();\
}

namespace szas
{
	class Identifier : public Base
	{
		public:
			explicit Identifier(const BaseDescriptor& descriptor) :
				Base(descriptor) { }

			virtual size_t GetTypeID() const noexcept = 0;
	};

	template <typename T>
	concept HasTypeID = std::is_same_v<typename T::type_id_tag, T>;
}