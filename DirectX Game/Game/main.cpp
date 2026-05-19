#include <SZAS/All.h>

int main()
{
	try
	{
		szas::Game game({{1280,720}, szas::Logger::LogLevel::Information });
		game.Run();
	} //Catch runtime errors
	catch(const std::runtime_error&)
	{
		return EXIT_FAILURE;
	} //Catch any exception of type invalid argument
	catch(const std::invalid_argument)
	{
		return EXIT_FAILURE;
	} //Catch generic exceptions
	catch (const std::exception&)
	{
		return EXIT_FAILURE;
	} //Catch any exceptions not specified above (catch all handler)
	catch (...)
	{
		return EXIT_FAILURE;
	}


	return EXIT_SUCCESS;
}