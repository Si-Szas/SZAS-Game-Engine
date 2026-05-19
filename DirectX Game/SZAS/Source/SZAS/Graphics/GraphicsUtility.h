#pragma once
#include <SZAS/Core/Common.h>

namespace szas
{
	//Creating a namespace for purely helper functions
	//Good to avoid stateless utility classes and use namespaces instead
	namespace GraphicsUtility 
	{
		//Gets shader model target, returns string
		//Having inline allows it to be included in multiple translation units without causing linker errors
		//Inline ensures safe linkage and reuse
		inline const char* GetShaderModelTarget(ShaderType type)
		{
			switch (type)
			{
				//Vertex/Pixel Shader, 5.0 is shader model version
				case szas::ShaderType::VertexShader: return "vs_5_0"; break;
				case szas::ShaderType::PixelShader:	return "ps_5_0";  break;
				default: return "";
			}
		}
	}
}