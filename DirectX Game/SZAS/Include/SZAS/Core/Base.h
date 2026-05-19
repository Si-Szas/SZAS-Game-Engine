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

//Macro to log error messages
#define SZASLogInformation(message)\
	SZASLog(GetLogger(), Logger::LogLevel::Information, message);

#define SZASLogWarning(message)\
	SZASLog(GetLogger(), Logger::LogLevel::Warning, message);

#define SZASLogError(message)\
	SZASLog(GetLogger(), Logger::LogLevel::Error, message);
	//Place enumeration in () to avoid errors

	//Create a macro using the defined preprocesser directive
	//Tells compiler to replace all instances of a specific name of a value before compilation	
#define SZASLogThrowError(message)\
	SZASLogThrow(GetLogger(), std::runtime_error, Logger::LogLevel::Error, message)

	//Throw an invalid argument exception (not run-time error)
#define SZASLogThrowInvalidArgument(message)\
	SZASLogThrow(GetLogger(), std::invalid_argument, Logger::LogLevel::Error, message)