#include <SZAS/InputSystem/InputSystem.h>
#include <SZAS/Core/Identifier.h>
#include <SZAS/InputSystem/Commands/MoveForwardCommand.h>
#include <SZAS/InputSystem/Commands/MoveLeftCommand.h>
#include <SZAS/InputSystem/Commands/MoveBackwardCommand.h>
#include <SZAS/InputSystem/Commands/MoveRightCommand.h>
#include <ranges>
#include <Windows.h>

szas::InputSystem::InputSystem(const InputSystemDescriptor& descriptor) :
	Base(descriptor.base)
{
	BindWKeyCommand(new MoveForwardCommand(descriptor));
	BindAKeyCommand(new MoveLeftCommand(descriptor));
	BindSKeyCommand(new MoveBackwardCommand(descriptor));
	BindDKeyCommand(new MoveRightCommand(descriptor));
}

void szas::InputSystem::Update()
{
	m_previousKeys = m_currentKeys;

	for (auto i : std::views::iota(0u, static_cast<std::size_t>(KeyCode::Count)))
	{
		const auto vk = GetInternalKeyCode(static_cast<KeyCode>(i));
		m_currentKeys[i] = (GetAsyncKeyState(vk) & 0x8000) != 0;
	}

	m_previousMousePosition = m_mousePosition;

	POINT point{};
	GetCursorPos(&point);

	m_mousePosition.x = static_cast<f32>(point.x);
	m_mousePosition.y = static_cast<f32>(point.y);

	m_mouseDelta.x = m_mousePosition.x - m_previousMousePosition.x;
	m_mouseDelta.y = m_mousePosition.y - m_previousMousePosition.y;

	if (m_cursorLocked) CenterCursor();
}

szas::InputCommand* szas::InputSystem::HandleInput()
{
	if (IsKeyDown(szas::KeyCode::W)) return WKeyCommand;
	else if (IsKeyDown(szas::KeyCode::A)) return AKeyCommand;
	else if (IsKeyDown(szas::KeyCode::S)) return SKeyCommand;
	else if (IsKeyDown(szas::KeyCode::D)) return DKeyCommand;
	else return NULL;
}

void szas::InputSystem::BindWKeyCommand(InputCommand* newCommandBind)
{
	//If the key is already binded somewhere, delete that
	if (WKeyCommand != nullptr) delete WKeyCommand;

	WKeyCommand = newCommandBind;
}

void szas::InputSystem::BindAKeyCommand(InputCommand* newCommandBind)
{
	if (AKeyCommand != nullptr) delete AKeyCommand;

	AKeyCommand = newCommandBind;
}

void szas::InputSystem::BindSKeyCommand(InputCommand* newCommandBind)
{
	if (SKeyCommand != nullptr) delete SKeyCommand;

	SKeyCommand = newCommandBind;
}

void szas::InputSystem::BindDKeyCommand(InputCommand* newCommandBind)
{
	if (DKeyCommand != nullptr) delete DKeyCommand;

	DKeyCommand = newCommandBind;
}

bool szas::InputSystem::IsKeyDown(KeyCode key) const
{
	return m_currentKeys[static_cast<std::size_t>(key)];
}

bool szas::InputSystem::IsKeyPressed(KeyCode key) const
{
	return m_currentKeys[static_cast<std::size_t>(key)] &&
		!m_previousKeys[static_cast<std::size_t>(key)];
}

bool szas::InputSystem::IsKeyReleased(KeyCode key) const
{
	return !m_currentKeys[static_cast<std::size_t>(key)] &&
		m_previousKeys[static_cast<std::size_t>(key)];
}

szas::Vec2 szas::InputSystem::GetMousePosition() const noexcept
{
	return m_mousePosition;
}

szas::Vec2 szas::InputSystem::GetMouseDelta() const noexcept
{
	return m_mouseDelta;
}

void szas::InputSystem::SetCursorVisible(bool visible)
{
	m_cursorVisible = visible;

	while (ShowCursor(visible) < 0 && visible) {}
	while (ShowCursor(visible) >= 0 && !visible) {}
}

void szas::InputSystem::SetCursorLocked(bool locked)
{
	m_cursorLocked = locked;
	if (locked) CenterCursor();
}

void szas::InputSystem::SetCursorLockArea(const Rect& lockedArea)
{
	m_lockedArea = lockedArea;
}

szas::InputSystem::~InputSystem()
{
	delete WKeyCommand;
	delete AKeyCommand;
	delete SKeyCommand;
	delete DKeyCommand;
}

short szas::InputSystem::GetInternalKeyCode(const KeyCode& key)
{
	const auto value = static_cast<int>(key);
	//Key inputs from A to Z
	if (key >= KeyCode::A && key <= KeyCode::Z) return 'A' + (value - static_cast<int>(KeyCode::A));
	//Key inputs from 0 to 9
	if (key >= KeyCode::Num0 && key <= KeyCode::Num9) return '0' + (value - static_cast<int>(KeyCode::Num0));
	
	switch (key)
	{
		case KeyCode::Shift: return VK_SHIFT;
		case KeyCode::Escape: return VK_ESCAPE;
		case KeyCode::Space: return VK_SPACE;
		case KeyCode::Enter: return VK_RETURN;
		case KeyCode::Up: return VK_UP;
		case KeyCode::Down: return VK_DOWN;
		case KeyCode::Left: return VK_LEFT;
		case KeyCode::Right: return VK_RIGHT;
		default: return 0;
	}
}

short szas::InputSystem::GetInternalMouseInput(const MouseInput& mouseInput)
{
	switch (mouseInput)
	{
		case MouseInput::MouseLeft: return VK_LBUTTON;
		case MouseInput::MouseMiddle: return VK_MBUTTON;
		case MouseInput::MouseRight: return VK_RBUTTON;
		default: return 0;
	}
}

void szas::InputSystem::CenterCursor()
{
	const auto centerX = m_lockedArea.left + (m_lockedArea.width / 2);
	const auto centerY = m_lockedArea.top + (m_lockedArea.height / 2);

	SetCursorPos(centerX, centerY);

	m_mousePosition.x = static_cast<f32>(centerX);
	m_mousePosition.y = static_cast<f32>(centerY);
}
