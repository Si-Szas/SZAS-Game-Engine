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
}

#define SZASLog(logger, type, message)\
	logger.Log((type), message)

#define SZASLogThrow(logger, exception, type, message)\
	{\
		SZASLog(logger, type, message);\
		throw exception(message);\
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