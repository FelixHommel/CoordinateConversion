#ifndef PLOTTER_H
#define PLOTTER_H

class Plotter
{
public:
	//Constructor / Destructor
	Plotter(sf::RenderWindow* window, pointPairs* points);
	~Plotter();

	void drawPlot(sf::RenderTarget* window);

	//Accessors
	const void printCoordinates() const;

	void render(sf::RenderTarget& target);

private:
	sf::VertexArray* plot;

	pointPairs* m_coordinates;

	void addPoints2Vertex();

};

#endif // !PLOTTER_H
