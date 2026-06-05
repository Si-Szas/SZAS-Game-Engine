#pragma once
#include <SZAS/Core/Common.h>

namespace szas 
{
	class Base
	{
		szas_disable_copy_and_move(Base)
		public:
			//CONSTRUCTOR
				//Explicitly declare that descriptor is used in read only mode
			explicit Base(const BaseDescriptor& descriptor);

			//DESTRUCTOR
			virtual ~Base();
			virtual Logger& GetLogger() noexcept final;
	
		protected:
			//Dependency injection, not singleton for logger
				//Pass the injection is a design pattern where you pass or inject an object dependencies from outside
			Logger& m_logger;
	};
}