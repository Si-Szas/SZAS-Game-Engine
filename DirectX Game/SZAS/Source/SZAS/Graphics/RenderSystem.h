#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/Core/Core.h>
#include <SZAS/Core/Base.h>
#include <d3d11.h>
#include <wrl.h>

namespace szas 
{
	class RenderSystem final: public Base
	{
		public:
			//CONSTRUCTOR
			explicit RenderSystem(const RenderSystemDescriptor& descriptor);
			//DESTRUCTOR
			virtual ~RenderSystem() override;

		private:
			//We cannot use smart pointers for D3D Devices. Instead we use Com Objects
			//Use reference counting for memory management. Counts how many references or owners point to it.
			//When reference count = 0, object is destroyed
			Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice{};
			//Device object
			Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_d3dContext{};
	};
}
