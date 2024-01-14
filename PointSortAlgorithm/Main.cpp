#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <sstream>

constexpr auto DEBUG_MODE = true;

int main(int argc, char* argv[])
{
	if(argc >1)
		if(DEBUG_MODE)
			std::cout << argv[1] << std::endl;
	else
	{
		std::cout << "No File provided. Exiting..." << std::endl;
		exit(0);
	}

	std::ifstream inputFile{ argv[1] };
	if (DEBUG_MODE)
		std::cout << std::boolalpha << "The File is open: " << inputFile.is_open() << std::endl;

	//input data to a std::pair<float, float>

	inputFile.close();

	return 0;
}
