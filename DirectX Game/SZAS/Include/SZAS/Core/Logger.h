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
