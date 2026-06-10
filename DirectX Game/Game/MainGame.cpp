#include "MainGame.h"

using namespace szas;

MainGame::MainGame(const GameDescriptor& descriptor) :
	Game(descriptor)
{
}

void MainGame::OnCreate() 
{
	Game::OnCreate();
	auto& world = GetWorld();

	auto object = world.CreateAGameObject<AGameObject>();
	if(object)
	{
		auto transform = object->GetComponent<TransformComponent>();

		if (!transform) return;

		transform->SetPosition({ 10.0f, 10.0f, 10.0f });
		transform->SetRotation({ 2.0f, 1.5f, 2.0f });
	}

}

void MainGame::OnUpdate(f32 deltaTime)
{
	Game::OnUpdate(deltaTime);
}