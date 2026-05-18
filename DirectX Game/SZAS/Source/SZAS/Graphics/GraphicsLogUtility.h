#pragma once
#include <SZAS/Core/Logger.h>

namespace szas 
{
	#define SZASGraphicsLogThrowOnFail(hr, message)\
	{\
		auto res = (hr);\
		if(FAILED(res))\
			SZASLogErrorAndThrow(message);\
	}
}