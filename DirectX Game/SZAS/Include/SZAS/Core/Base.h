#pragma once
#include <SZAS/Core/Common.h>

namespace szas 
{
	class Base
	{
		public:
			//CONSTRUCTOR
				//Explicitly declare that descriptor is used in read only mode
			explicit Base(const BaseDescriptor& descriptor);

			//DESTRUCTOR
			virtual ~Base();
			virtual Logger& GetLogger() noexcept final;
	
		protected:
			//RULE OF 5, prevents the copying of shallow-level data of a window (or anything) to a variable of the same type
				// Destructor
				// Copy Constrcutor
				// Move Constructor
				// Copy Assignment Operator
				// Move Assignment Operator
			Base(const Base&) = delete;
			Base(Base&&) = delete;
			Base& operator = (const Base&) = delete;
			Base& operator = (Base&&) = delete;

			//Dependency injection, not singleton for logger
				//Pass the injection is a design pattern where you pass or inject an object dependencies from outside
			Logger& m_logger;
	};
}