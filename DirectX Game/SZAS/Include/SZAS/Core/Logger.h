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
			void Log(LogLevel level, const char* message);

			//DESTRUCTOR
			~Logger();

		protected:
			//Never be possible to replace a log instance with a new one
			Logger(const Logger&) = delete;
			Logger(Logger&&) = delete;
			Logger& operator = (const Logger&) = delete;
			Logger& operator = (Logger&&) = delete;

		private:
			LogLevel m_logLevel = LogLevel::Error;
	
		
	};
	
	#define SZASLogInformation(message)\
		GetLogger().Log((Logger::LogLevel::Information), message);

	#define SZASLogWarning(message)\
		GetLogger().Log((Logger::LogLevel::Warning), message);

	//Macro to log error messages
	#define SZASLogError(message)\
		GetLogger().Log((Logger::LogLevel::Error), message);
		//Place enumeration in () to avoid errors

	//Create a macro using the defined preprocesser directive
	//Tells compiler to replace all instances of a specific name of a value before compilation	
	#define SZASLogErrorAndThrow(message)\
	{\
		SZASLogError(message);\
		throw std::runtime_error(message);\
	}

}
