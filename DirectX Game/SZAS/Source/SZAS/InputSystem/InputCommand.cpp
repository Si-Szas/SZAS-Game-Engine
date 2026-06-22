#include <SZAS/InputSystem/InputCommand.h>

szas::InputCommand::InputCommand(const InputSystemDescriptor& descriptor) :
	Identifier({descriptor.base})
{
}

szas::InputCommand::~InputCommand()
{
}
