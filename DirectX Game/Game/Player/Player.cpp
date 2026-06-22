#include "Player.h"
#include <SZAS/AComponent/TransformComponent.h>
#include <SZAS/InputSystem/InputSystem.h>
#include <SZAS/InputSystem/InputCommand.h>
#include <SZAS/InputSystem/Commands/MoveForwardCommand.h>
#include <SZAS/InputSystem/Commands/MoveRightCommand.h>
#include <SZAS/InputSystem/Commands/MoveLeftCommand.h>
#include <SZAS/InputSystem/Commands/MoveBackwardCommand.h>

#include <iostream>

szas::Player::Player(const AGameObjectDescriptor& descriptor) :
	AGameObject(descriptor)
{
}

void szas::Player::OnCreate()
{
	m_camera = CreateOrGetComponent<CameraComponent>();
}

void szas::Player::OnUpdate(f32 deltaTime)
{
	auto& input = GetInputSystem();

	auto sensitivity = 0.001f;
	auto rotation = GetTransform().GetRotation();
	rotation.x += GetInputSystem().GetMouseDelta().y * sensitivity;
	rotation.y += GetInputSystem().GetMouseDelta().x * sensitivity;
	if (rotation.x > 1.57f) rotation.x = 1.57f;
	else if (rotation.x < -1.57f) rotation.x = -1.57f;
	GetTransform().SetRotation(rotation);

	auto position = GetTransform().GetPosition();
	//auto f = 0.0f;
	//auto r = 0.0f;
	//auto s = 3.0f;
	//
	//if (GetInputSystem().IsKeyDown(szas::KeyCode::W)) f = 1.0f;
	//if (GetInputSystem().IsKeyDown(szas::KeyCode::S)) f = -1.0f;
	//if (GetInputSystem().IsKeyDown(szas::KeyCode::D)) r = 1.0f;
	//if (GetInputSystem().IsKeyDown(szas::KeyCode::A)) r = -1.0f;

	ResetMovementModifiers();

	InputCommand* command = GetInputSystem().HandleInput();
	if (command) 
	{
		size_t commandType = command->GetTypeID();

		if (commandType == szas::MoveForwardCommand::getTypeId()) command->ExecuteCommand(*this);
		if (commandType == szas::MoveRightCommand::getTypeId()) command->ExecuteCommand(*this);
		if (commandType == szas::MoveLeftCommand::getTypeId()) command->ExecuteCommand(*this);
		if (commandType == szas::MoveBackwardCommand::getTypeId()) command->ExecuteCommand(*this);
	
		//Record the command that was just executed
		GetInputSystem().RecordCommand(command);
	}

	/// TEMPORARY ///
	if (GetInputSystem().IsKeyDown(szas::KeyCode::LeftControl) || GetInputSystem().IsKeyDown(szas::KeyCode::RightControl))
	{
		std::cout << "Holding CTRL" << std::endl;
		if (GetInputSystem().IsKeyPressed(szas::KeyCode::Z)) // Pressed this frame
		{
			std::cout << "Command Undoed" << std::endl;
			GetInputSystem().UndoCommand(*this);
		}
		else if (GetInputSystem().IsKeyPressed(szas::KeyCode::Y))
		{
			std::cout << "Command Redoed" << std::endl;
			GetInputSystem().RedoCommand(*this);
		}
	}

	//auto forwardDir = GetTransform().Forward() * GetForwardModifier();
	//auto rightDir = GetTransform().Right() * GetRightModifier();
	//auto directionSum = forwardDir + rightDir;
	//
	//if (szas::Vec3::LengthSquared(directionSum) > 0.001f)
	//{
	//	auto direction = szas::Vec3::Normalize(directionSum);
	//	position = position + direction * GetSpeedModifier() * deltaTime;
	//}
	//
	//GetTransform().SetPosition(position);
}

szas::Player::~Player()
{
}
