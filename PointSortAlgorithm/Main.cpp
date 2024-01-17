//cstdlib
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <thread>
//#include <stdfloat> //C++23 only

//Boost
#include <boost/multiprecision/cpp_dec_float.hpp>

constexpr auto DEBUG_MODE = true;
using pFloat = boost::multiprecision::cpp_dec_float_100;

template <typename  T>
static void printPair(std::pair<T, T>& pair)
{
	std::cout << pair.first << " " << pair.second << std::endl;
}

template <typename  T>
static void printPointPairs(std::vector<std::pair<T, T>>& pointPairs)
{
	for (std::pair<T, T>& pair : pointPairs)
		printPair(pair);
}

template <typename T>
static void writeToFile(std::string& filepath, std::vector<std::pair<T, T>>& pointPairs)
{
	std::ofstream outputFile{ filepath };

	if (!outputFile.is_open())
	{
		std::cerr << "Failed saving the results to a File. Please try again..." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		exit(0);
	}

	outputFile << std::setprecision(std::numeric_limits<boost::multiprecision::cpp_dec_float_100>::max_digits10);

	for (std::pair<T, T>& pair : pointPairs)
	{
		outputFile << pair.first << " " << pair.second << std::endl;
	}

	outputFile.close();
	std::cout << "Saved results to " << filepath << "..." << std::endl;
}

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		if (DEBUG_MODE)
			std::cout << argv[1] << std::endl;
	}
	else
	{
		std::cout << "No File provided. Exiting..." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		exit(0);
	}

	//Step 1: Read in values
	std::ifstream inputFile{ argv[1] };

	if (DEBUG_MODE)
		std::cout << std::boolalpha << "The File is open: " << inputFile.is_open() << std::endl;

	std::string input;
	std::vector<std::pair<pFloat, pFloat>> pointPairs;

	while (std::getline(inputFile, input))
	{
		std::stringstream inLine{ input };
		pFloat x;
		pFloat y;

		inLine >> std::setprecision(std::numeric_limits<boost::multiprecision::cpp_dec_float_100>::max_digits10) >> x >> y;

		std::pair<pFloat, pFloat> p(x, y);
		pointPairs.push_back(p);

		if (DEBUG_MODE)
		{
			printPair(p);
		}
	}

	inputFile.close();

	//Step 2: Bring pairs into right order
	//std::reverse(pointPairs.begin(), pointPairs.end());

	//Step 3: Divide by greatest number


	//Step 4: Save to File
	std::string outFileLocation{ "data/out.txt" };
	writeToFile(outFileLocation, pointPairs);

	return 0;
}
