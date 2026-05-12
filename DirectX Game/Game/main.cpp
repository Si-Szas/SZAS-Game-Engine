#include <DX3D/All.h>

int main()
{
	try
	{
		dx3d::Game game{};
		game.run();
	} //Catch runtime errors
	catch(const std::runtime_error&)
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