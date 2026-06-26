#include "Player.h"
#include <SZAS/Game/WorldRenderer.h>
#include <SZAS/Graphics/GraphicsDevice/GraphicsDevice.h>
#include <SZAS/AComponent/TransformComponent.h>
#include <SZAS/InputSystem/InputSystem.h>
#include <SZAS/InputSystem/InputCommand.h>
#include <SZAS/InputSystem/Commands/MoveForwardCommand.h>
#include <SZAS/InputSystem/Commands/MoveRightCommand.h>
#include <SZAS/InputSystem/Commands/MoveLeftCommand.h>
#include <SZAS/InputSystem/Commands/MoveBackwardCommand.h>
#include <SZAS/InputSystem/Commands/CreateAGameObjectCommand.h>
#include <SZAS/InputSystem/Commands/DeleteAGameObjectCommand.h>
#include <SZAS/InputSystem/Commands/DeleteAllAGameObjectsCommand.h>
#include <SZAS/InputSystem/Commands/ExitApplicationCommand.h>

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
	auto& world = GetWorld();
	auto& inputSystem = GetInputSystem();

	auto sensitivity = 0.001f;
	auto rotation = GetTransform().GetRotation();
	rotation.x += inputSystem.GetMouseDelta().y * sensitivity;
	rotation.y += inputSystem.GetMouseDelta().x * sensitivity;
	if (rotation.x > 1.57f) rotation.x = 1.57f;
	else if (rotation.x < -1.57f) rotation.x = -1.57f;
	GetTransform().SetRotation(rotation);

	auto position = GetTransform().GetPosition();

	ResetMovementModifiers();

	InputCommand* command = inputSystem.HandleInput();
	if (command) 
	{
		size_t commandType = command->GetTypeID();

		if (commandType == szas::MoveForwardCommand::getTypeId()) command->ExecuteCommand(*this, world);
		if (commandType == szas::MoveRightCommand::getTypeId()) command->ExecuteCommand(*this, world);
		if (commandType == szas::MoveLeftCommand::getTypeId()) command->ExecuteCommand(*this, world);
		if (commandType == szas::MoveBackwardCommand::getTypeId()) command->ExecuteCommand(*this, world);
		//if (commandType == szas::CreateAGameObjectCommand::getTypeId()) command->ExecuteCommand(*this, world);
		//if (commandType == szas::DeleteAGameObjectCommand::getTypeId()) command->ExecuteCommand(*this, world);
		//if (commandType == szas::DeleteAllAGameObjectsCommand::getTypeId()) command->ExecuteCommand(*this, world);
		if (commandType == szas::ExitApplicationCommand::getTypeId()) command->ExecuteCommand();
	
		//Record the command that was just executed
		inputSystem.RecordCommand(command);
	}

	/// TEMPORARY ///
	//if (inputSystem.IsKeyDown(szas::KeyCode::LeftControl) || inputSystem.IsKeyDown(szas::KeyCode::RightControl))
	//{
	//	std::cout << "Holding CTRL" << std::endl;
	//	if (inputSystem.IsKeyPressed(szas::KeyCode::Z)) // Pressed this frame
	//	{
	//		std::cout << "Command Undoed" << std::endl;
	//		inputSystem.UndoCommand(*this);
	//	}
	//	else if (inputSystem.IsKeyPressed(szas::KeyCode::Y))
	//	{
	//		std::cout << "Command Redoed" << std::endl;
	//		inputSystem.RedoCommand(*this);
	//	}
	//}

	auto forwardDir = GetTransform().Forward() * GetForwardModifier();
	auto rightDir = GetTransform().Right() * GetRightModifier();
	auto directionSum = forwardDir + rightDir;
	
	if (szas::Vec3::LengthSquared(directionSum) > 0.001f)
	{
		auto direction = szas::Vec3::Normalize(directionSum);
		position = position + direction * GetSpeedModifier() * deltaTime;
	}
	
	GetTransform().SetPosition(position);
}

szas::Player::~Player()
{
}
