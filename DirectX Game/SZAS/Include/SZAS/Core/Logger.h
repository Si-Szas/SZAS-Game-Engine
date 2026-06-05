#pragma once

#include <SZAS/Core/Core.h>
#include <format>

namespace szas{
	class Logger final
	{
		szas_disable_copy_and_move(Logger)
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
			template<typename... Args>
			void Log(LogLevel level, std::format_string<Args...> fmt, Args&&... args)
			{
				auto str = std::format(fmt, std::forward<Args>(args)...);
				_Log(level, str.c_str());
			}

			//DESTRUCTOR
			~Logger();

		private:
			void _Log(LogLevel level, const char* message);

		private:
			LogLevel m_logLevel = LogLevel::Error;
	
	};
}

#define SZASLog(logger, type, message, ...)\
	logger.Log((type), {message} __VA_OPT__(,) __VA_ARGS__);

#define SZASLogThrow(logger, exception, type, message, ...)\
	{\
		SZASLog(logger,type,message, __VA_ARGS__);\
		throw exception(message);\
	}

//Macro to log error messages
#define SZASLogInformation(message, ...)\
	SZASLog(GetLogger(), Logger::LogLevel::Information, message, __VA_ARGS__)

#define SZASLogWarning(message, ...)\
	SZASLog(GetLogger(), Logger::LogLevel::Warning, message, __VA_ARGS__)

//Place enumeration in () to avoid errors
#define SZASLogError(message, ...)\
	SZASLog(GetLogger(), Logger::LogLevel::Error, message, __VA_ARGS__)

//Create a macro using the defined preprocesser directive
//Tells compiler to replace all instances of a specific name of a value before compilation	
#define SZASLogThrowError(message, ...)\
	SZASLogThrow(GetLogger(), std::runtime_error, Logger::LogLevel::Error, message, __VA_ARGS__)

//Throw an invalid argument exception (not run-time error)
#define SZASLogThrowInvalidArgument(message, ...)\
	SZASLogThrow(GetLogger(), std::invalid_argument, Logger::LogLevel::Error, message, __VA_ARGS__)