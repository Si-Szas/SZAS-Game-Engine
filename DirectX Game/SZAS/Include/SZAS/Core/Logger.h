#pragma once

namespace szas{
	class Logger final
	{
		public:
			//ENUMS
			enum class LogLevel {
				Error = 0,
				Warning,
				Information
			};

			//CONSTRUCTOR
			//Explicit has single argument constructors
			explicit Logger(LogLevel logLevel = LogLevel::Error);

			//Log Method
			//const tells function that the function doesn't alter state of the class
			void log(LogLevel level, const char* message) const;

		private:
			LogLevel m_logLevel = LogLevel::Error;
	
		
	};
	
	//Macro to log error messages
	#define SZASLogError(message)\
		getLogger().log((Logger::LogLevel::Error), message);
		//Place enumeration in () to avoid errors

	//Create a macro using the defined preprocesser directive
	//Tells compiler to replace all instances of a specific name of a value before compilation	
	#define SZASLogErrorAndThrow(message)\
	{\
		SZASLogError(message);\
		throw std::runtime_error(message);\
	}

}
