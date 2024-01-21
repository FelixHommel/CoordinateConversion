#ifndef PLOTTER_H
#define PLOTTER_H

class Plotter
{
public:
	//Constructor / Destructor
	Plotter(const unsigned int posX, const unsigned int posY, const unsigned int width, const unsigned int height, pointPairs* points = nullptr);
	~Plotter();

	//Accessors
	const void printCoordinates() const;

	void render(sf::RenderTarget& target);

private:
	unsigned int m_plotPosX;
	unsigned int m_plotPosY;
	unsigned int m_plotWidth;
	unsigned int m_plotHeight;

	sf::Texture m_plot;
	sf::Image image;
	sf::Sprite m_sprite;

	std::vector<std::pair<pFloat, pFloat>>* m_coordinates;

	void init();

};

#endif // !PLOTTER_H
