#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <sstream>
#include <algorithm>

constexpr auto DEBUG_MODE = true;

template <typename  T>
void printPair(std::pair<T, T>& pair)
{
	std::cout << pair.first() << " " << pair.second() << std::endl;
}

void printPointPairs(std::vector<std::pair<float, float>> pointPairs)
{
	for (std::pair<float, float> pair : pointPairs)
	{
		std::cout << pair.first() << " " << pair.second() << std::endl;
	}
}

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
	std::string input;
	std::vector<std::pair<float, float>> pointPairs;
	while (std::getline(inputFile, input))
	{
		std::stringstream inLine{ input };
		std::string x;
		std::string y;
		if (inLine >> x >> y)
		{
			std::pair<float, float> p(std::stof(x), std::stof(y));
			pointPairs.push_back(p);
			if (DEBUG_MODE)
				printPair(p);
				//std::cout << "x=" << x << " | y=" << y << std::endl;
		}
	}

	inputFile.close();

	pointPairs.reserve();

	return 0;
}
