#pragma once
#include <SZAS/Core/Logger.h>
#include <SZAS/Core/Base.h>
#include <d3d11.h>

namespace szas 
{
	namespace GraphicsLogUtility
	{
		inline void CheckShaderCompile(Logger& logger, HRESULT hr, ID3DBlob* errorBlob) 
		{
			//If function failed, either we have error messages or we dont
				//If error blob is not null, we can retrieve the actual error message via GetBufferPointer
				//Method returns void pointer, which we can cast it to a const char pointer
				//If error blob unavailable, assign nullptr
			auto errorMsg = errorBlob ? static_cast<const char*>(errorBlob->GetBufferPointer()) : nullptr;

			if (FAILED(hr))
				SZASLogThrow(logger, std::runtime_error, Logger::LogLevel::Error, errorMsg ? errorMsg : "Shader Compilation failed.");
			
			//If the function succeeded but there are still messages, then there are warnings
			if(errorMsg) 
				SZASLog(logger, Logger::LogLevel::Warning, errorMsg);

		}
	}
}

#define SZASGraphicsLogThrowOnFail(hr, message)\
	{\
		auto res = (hr);\
		if(FAILED(res))\
			SZASLogThrowError(message);\
	}

//Make calling this function easier, lets define macro below
#define SZASGraphicsCheckShaderCompile(hr, errorBlob)\
	{\
		auto res = (hr);\
		szas::GraphicsLogUtility::CheckShaderCompile(GetLogger(), res, errorBlob);\
	}