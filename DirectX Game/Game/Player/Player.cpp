#include "Player.h"
#include <SZAS/AComponent/TransformComponent.h>
#include <SZAS/InputSystem/InputSystem.h>
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
	auto rot = GetTransform().GetRotation();
	rot.x += GetInputSystem().GetMouseDelta().y * sensitivity;
	rot.y += GetInputSystem().GetMouseDelta().x * sensitivity;
	if (rot.x > 1.57f) rot.x = 1.57f;
	else if (rot.x < -1.57f) rot.x = -1.57f;
	GetTransform().SetRotation(rot);


	auto pos = GetTransform().GetPosition();
	auto forward = 0.0f;
	auto right = 0.0f;
	auto speed = 3.0f;
	if (GetInputSystem().IsKeyDown(szas::KeyCode::W)) {
		forward = 1.0f;
		std::cout << "W Key Pressed!" << std::endl;
	}

	if (GetInputSystem().IsKeyDown(szas::KeyCode::S)) {
		forward = -1.0f;
		std::cout << "S Key Pressed!" << std::endl;
	}
	if (GetInputSystem().IsKeyDown(szas::KeyCode::D)) {
		right = 1.0f;
		std::cout << "D Key Pressed!" << std::endl;
	}
	if (GetInputSystem().IsKeyDown(szas::KeyCode::A)) {
		right = -1.0f;
		std::cout << "A Key Pressed!" << std::endl;
	}
	auto forwardDir = GetTransform().Forward() * forward;
	auto rightDir = GetTransform().Right() * right;
	auto direction = szas::Vec3::normalize(forwardDir + rightDir);
	pos = pos + direction * speed * deltaTime;
	GetTransform().SetPosition(pos);
}

szas::Player::~Player()
{
}
