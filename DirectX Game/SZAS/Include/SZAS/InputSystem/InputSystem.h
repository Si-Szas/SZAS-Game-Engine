#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/Core/Base.h>
#include <SZAS/Math/Vec2.h>
#include <SZAS/Math/Rect.h>
#include <array>

namespace szas
{
	class InputSystem final : public Base
	{
		public:
			//CONSTRUCTOR
			explicit InputSystem(const InputSystemDescriptor& descriptor);
			
			//FUNCTIONS
			void Update();

			//CHECKERS
			bool IsKeyDown(KeyCode key) const;
			bool IsKeyPressed(KeyCode key) const;
			bool IsKeyReleased(KeyCode key) const;

			//GETTERS
			Vec2 GetMousePosition() const noexcept;
			Vec2 GetMouseDelta() const noexcept;

			//SETTERS
			void SetCursorVisible(bool visible);
			void SetCursorLocked(bool locked);
			void SetCursorLockArea(const Rect& lockedArea);
			
			//DESTRUCTOR
			virtual ~InputSystem();

		private:
			//FUNCTIONS
			short GetInternalKeyCode(const KeyCode& key);
			short GetInternalMouseInput(const MouseInput& mouseInput);
			void CenterCursor();

		private:
			std::array<bool, static_cast<std::size_t>(KeyCode::Count)> m_currentKeys{};
			std::array<bool, static_cast<std::size_t>(KeyCode::Count)> m_previousKeys{};

			Vec2 m_mousePosition{};
			Vec2 m_previousMousePosition{};
			Vec2 m_mouseDelta{};

			Rect m_lockedArea{};

			bool m_cursorVisible{ true };
			bool m_cursorLocked{ false };
	};
}
