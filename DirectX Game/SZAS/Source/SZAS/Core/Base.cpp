#include <SZAS/Core/Base.h>
using namespace szas;

szas::Base::Base(const BaseDescriptor& descriptor): m_logger(descriptor.logger)
{

}

Logger& szas::Base::GetLogger() noexcept
{
	return m_logger;
}

szas::Base::~Base()
{

}