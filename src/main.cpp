#include "main.hpp"

int main(int argc, char* argv[])
{
	std::cout << "Argument Count: " << argc << std::endl;

	for(int i = 0; i < argc; i++)
	{
		std::cout << argv[i] << std::endl;
	}

	return 0;
}