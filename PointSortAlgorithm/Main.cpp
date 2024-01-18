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

//Boost Library (may not work without the correct project settings)
#include <boost/multiprecision/cpp_dec_float.hpp>

//Global variables
constexpr auto DEBUG_MODE = true;
using pFloat = boost::multiprecision::cpp_dec_float_100;

//Print a singel std::pair to console
template <typename  T>
static void printPair(std::pair<T, T>& pair)
{
	std::cout << std::setprecision(8) << pair.first << " " << pair.second << std::endl;
}

//print an entire vector of std::pairs to console
template <typename  T>
static void printPointPairs(std::vector<std::pair<T, T>>& pointPairs)
{
	for (std::pair<T, T>& pair : pointPairs)
		printPair(pair);
}

//write a vector of std::pair to a file
template <typename T>
static void writeToFile(const std::string& filepath, std::vector<std::pair<T, T>>& pointPairs)
{
	std::ofstream outputFile{ filepath };

	if (!outputFile.is_open())
	{
		std::cerr << "Failed saving the results to a File. Please try again..." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		exit(0);
	}

	//outputFile << std::setprecision(std::numeric_limits<boost::multiprecision::cpp_dec_float_100>::max_digits10);
	outputFile << std::setprecision(8);

	for (std::pair<T, T>& pair : pointPairs)
	{
		outputFile << pair.first << " " << pair.second << std::endl;
	}

	outputFile.close();
	std::cout << "Saved results to " << filepath << "..." << std::endl;
}

//Read in values from a file
static std::vector<std::pair<pFloat, pFloat>> inputValues(const std::string& filepath)
{
	std::ifstream inputFile{ filepath };

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

	return pointPairs;
}

//Sort the vector of std::pair
template<typename T>
static std::vector<std::pair<T, T>> sortList(std::vector<std::pair<T, T>>& in)
{
	std::vector<std::pair<T, T>> pos;
	std::vector<std::pair<T, T>> neg;

	for (size_t i{ 0 }; i < in.size(); ++i)
	{
		if (in.at(i).second < 0)
			neg.push_back(in.at(i));
		else
			pos.push_back(in.at(i));
	}

	std::sort(pos.begin(), pos.end(), [](const std::pair<pFloat, pFloat>& p1, const std::pair<pFloat, pFloat>& p2) { return p1.first > p2.first; });
	std::sort(neg.begin(), neg.end(), [](const std::pair<pFloat, pFloat>& p1, const std::pair<pFloat, pFloat>& p2) { return p1.first < p2.first; });

	for (size_t i{ 0 }; i < neg.size(); ++i)
	{
		pos.push_back(neg.at(i));
	}

	return pos;
}

//find the greatest value across every std::pair
template<typename T>
static const T findGreatest(std::vector<std::pair<T, T>>& in)
{
	T greatest{0};

	for (auto& p : in)
	{
		if (p.first > greatest)
		{
			greatest = p.first;
			std::cout << "New greatest: " << greatest << std::endl;
		}
	}

	return greatest;
}

//Generalize all values 
template<typename T>
static std::vector<std::pair<T, T>> generalize(std::vector<std::pair<T, T>> in)
{
	T divisor{ findGreatest(in) };
	std::cout << "Divisor: " << divisor << std::endl;

	std::vector<std::pair<T, T>> res{ in };

	for (size_t i{ 0 }; i < res.size(); ++i)
	{
		std::pair<T, T> p{ res.at(i) };
		
		p.first /= divisor;
		p.second /= divisor;

		res.at(i) = p;
	}

	return res;
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

	std::string filepath{ argv[1] };
	//Step 1: Read in values
	std::vector<std::pair<pFloat, pFloat>> pointPairs{ inputValues(filepath) };

	//Step 2: Bring pairs into right order
	pointPairs = sortList(pointPairs);

	//Step 3: Divide by greatest number
	pointPairs = generalize(pointPairs);

	//Step 4: Save to File
	std::string outFileLocation{ "data/out.txt" };
	writeToFile(outFileLocation, pointPairs);

	return 0;
}
