#include <SZAS/InputSystem/Commands/CreateAGameObjectCommand.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/Game/World.h>
#include <SZAS/AGameObject/Sphere.h>
#include <SZAS/AComponent/TransformComponent.h>
#include <SZAS/Math/Vec3.h>
#include <random>

szas::CreateAGameObjectCommand::CreateAGameObjectCommand(const InputSystemDescriptor& descriptor) :
	InputCommand(descriptor)
{
}

void szas::CreateAGameObjectCommand::ExecuteCommand()
{
	static std::random_device randDevice;
	static std::mt19937 generator(randDevice());
	std::uniform_real_distribution<f32> dis(-0.5f, 0.5f);

	auto sphere = m_world.CreateAGameObject<szas::Sphere>();
	sphere->GetTransform().SetScale({ 1.0f });
	sphere->GetTransform().SetPosition({dis(generator), dis(generator), 0.0f});
	
	//random direction here
	Vec3 movementDir{ dis(generator), dis(generator), 0.0f };
	if (szas::Vec3::LengthSquared(movementDir) < 0.001f)
	{
		movementDir = Vec3(1.0f, 0.0f, 0.0f);
	}

	Vec3::Normalize(movementDir);
	sphere->SetVelocity(movementDir);
}

void szas::CreateAGameObjectCommand::ExecuteCommand(AGameObject& gameObject)
{

}

void szas::CreateAGameObjectCommand::UndoCommand(AGameObject& gameObject)
{

}

szas::CreateAGameObjectCommand::~CreateAGameObjectCommand()
{

}