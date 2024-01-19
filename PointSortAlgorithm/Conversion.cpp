#include "stdafx.h"
#include "Conversion.h"

//Constructor
Conversion::Conversion()
{
}

//Destructor
Conversion::~Conversion()
{
}

//Access function
/// <summary>
/// Calculate function, which is called from outside to start the calculation progress
/// </summary>
/// <param name="inputFilepath">const std::string : location of the input file</param>
/// <param name="outputFilepath">const std::string : location of the output file</param>
void Conversion::calculate(const std::string& inputFilepath, const std::string& outputFilepath)
{
	m_pointPairs = readPairs(inputFilepath);
	m_pointPairs = sortPairs();
	m_pointPairs = generalize();
	saveToFile(outputFilepath);
}

/// <summary>
/// Print a single pair to the console, DEBUG only
/// </summary>
/// <param name="p">const std::pair<pFloat, pFloat> : pair which will get printed</param>
void Conversion::printPair(const std::pair<pFloat, pFloat>& p)
{
	std::cout << std::setprecision(8) << p.first << " " << p.second << std::endl;
}

/// <summary>
/// Print a vector of pairs to console, DEBUG only
/// </summary>
/// <param name="pairs">const pointPairs : vector of pairs that will get written to console</param>
void Conversion::printPointPairs(const pointPairs& pairs)
{
	for (const std::pair<pFloat, pFloat>& pair : pairs)
		printPair(pair);
}

//Private helper functions
/// <summary>
/// Read in the pairs from the input file
/// </summary>
/// <param name="inputFilepath">(const std::string : location of the input file</param>
/// <returns>Read in pairs</returns>
pointPairs Conversion::readPairs(const std::string& inputFilepath)
{
	std::ifstream inputFile{ inputFilepath };

	if (DEBUG_MODE)
		std::cout << std::boolalpha << "The File is open: " << inputFile.is_open() << std::endl;

	std::string input;
	pointPairs pairs;

	while (std::getline(inputFile, input))
	{
		std::stringstream inLine{ input };
		pFloat x;
		pFloat y;

		inLine >> std::setprecision(std::numeric_limits<boost::multiprecision::cpp_dec_float_100>::max_digits10) >> x >> y;

		std::pair<pFloat, pFloat> p(x, y);
		pairs.push_back(p);

		if (DEBUG_MODE)
		{
			printPair(p);
		}
	}

	inputFile.close();

	return pairs;
}

/// <summary>
/// Sort the pairs
/// </summary>
/// <returns>Sorted pairs</returns>
pointPairs Conversion::sortPairs()
{
	pointPairs positive;
	pointPairs negative;

	for (size_t i{ 0 }; i < m_pointPairs.size(); ++i)
	{
		if (m_pointPairs.at(i).second < 0)
			negative.push_back(m_pointPairs.at(i));
		else
			positive.push_back(m_pointPairs.at(i));
	}

	std::sort(positive.begin(), positive.end(), [](const std::pair<pFloat, pFloat>& p1, const std::pair<pFloat, pFloat>& p2) { return p1.first > p2.first; });
	std::sort(negative.begin(), negative.end(), [](const std::pair<pFloat, pFloat>& p1, const std::pair<pFloat, pFloat>& p2) { return p1.first < p2.first; });

	for (size_t i{ 0 }; i < negative.size(); ++i)
	{
		positive.push_back(negative.at(i));
	}

	return positive;
}

/// <summary>
/// Find the greatest x across all pairs
/// </summary>
/// <returns>Greatest x in all pairs</returns>
pFloat Conversion::findGreatest()
{
	/*
	* Technically redundand because the greatest x is always at the first pair in the vector because of the way it is sorted??
	*/
	pFloat greatest{ 0 };

	for (auto& p : m_pointPairs)
	{
		if (p.first > greatest)
		{
			greatest = p.first;
			std::cout << "New greatest: " << greatest << std::endl;
		}
	}

	return greatest;
}

/// <summary>
/// Generalize the points to bring them all in a relative distance to each other.
/// </summary>
/// <returns>Generalized pairs</returns>
pointPairs Conversion::generalize()
{
	pFloat divisor{ findGreatest() };

	pointPairs result{ m_pointPairs };

	for (size_t i{ 0 }; i < result.size(); ++i)
	{
		std::pair<pFloat, pFloat> p{ result.at(i) };

		p.first /= divisor;
		p.second /= divisor;

		result.at(i) = p;
	}

	return result;
}

/// <summary>
/// Save the final pairs to the output file
/// </summary>
/// <param name="outputFilepath">const std::string : output file location</param>
void Conversion::saveToFile(const std::string& outputFilepath)
{
	std::ofstream outputFile{ outputFilepath };

	if (!outputFile.is_open())
	{
		std::cerr << "Failed saving the results to a File. Please try again..." << std::endl;
	}

	outputFile << std::setprecision(8) << std::endl;

	for (const std::pair<pFloat, pFloat>& pair : m_pointPairs)
	{
		outputFile << pair.first << " " << pair.second << std::endl;
	}

	outputFile.close();
	std::cout << "Saved results to " << outputFilepath << "..." << std::endl;
}
