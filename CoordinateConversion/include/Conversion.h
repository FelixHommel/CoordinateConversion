#ifndef CONVERSION_H
#define CONVERSION_H

class Conversion
{
public:
	//Constructor / Destructor
	Conversion();
	~Conversion();

	//Public functions
	pointPairs calculate(const std::string& inputFilepath = "");
	void saveToFile(const std::string& outputFilepath ="data/out.dat");

private:
	//Private members
	pointPairs m_pointPairs;

	//Private functions
	///DEBUG
	void printPair(const std::pair<pFloat, pFloat>& p);
	void printPointPairs(const pointPairs& pairs);
	/// DEBUG!

	pointPairs readPairs(const std::string& inputFilepath);

	void sortPairs(pointPairs& pairs);

	pFloat findGreatest();
	void normalize(pointPairs& pairs);

};

#endif // !CONVERSION_H
