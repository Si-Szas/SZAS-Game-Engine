#include <SZAS/InputSystem/InputCommand.h>

szas::InputCommand::InputCommand(const InputSystemDescriptor& descriptor) :
	Identifier({ descriptor.base }),
	m_base(descriptor.base),
	m_world(descriptor.world)
{
}

szas::InputCommand::~InputCommand()
{
}
