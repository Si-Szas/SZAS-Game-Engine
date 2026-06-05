#include <SZAS/Core/Base.h>
using namespace szas;

Base::Base(const BaseDescriptor& descriptor): m_logger(descriptor.logger)
{

}

Logger& Base::GetLogger() noexcept
{
	return m_logger;
}

Base::~Base()
{

}