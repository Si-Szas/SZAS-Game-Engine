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
	auto rotation = GetTransform().GetRotation();
	rotation.x += GetInputSystem().GetMouseDelta().y * sensitivity;
	rotation.y += GetInputSystem().GetMouseDelta().x * sensitivity;
	if (rotation.x > 1.57f) rotation.x = 1.57f;
	else if (rotation.x < -1.57f) rotation.x = -1.57f;
	GetTransform().SetRotation(rotation);

	auto position = GetTransform().GetPosition();
	auto forward = 0.0f;
	auto right = 0.0f;
	auto speed = 3.0f;

	if (GetInputSystem().IsKeyDown(szas::KeyCode::W)) forward = 1.0f;
	if (GetInputSystem().IsKeyDown(szas::KeyCode::S)) forward = -1.0f;
	if (GetInputSystem().IsKeyDown(szas::KeyCode::D)) right = 1.0f;
	if (GetInputSystem().IsKeyDown(szas::KeyCode::A)) right = -1.0f;

	auto forwardDir = GetTransform().Forward() * forward;
	auto rightDir = GetTransform().Right() * right;
	auto direction = szas::Vec3::Normalize(forwardDir + rightDir);

	position = position + direction * speed * deltaTime;
	GetTransform().SetPosition(position);
}

szas::Player::~Player()
{
}
