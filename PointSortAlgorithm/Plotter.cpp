#include "stdafx.h"
#include "Plotter.h"

Plotter::Plotter(const unsigned int posX, const unsigned int posY, const unsigned int width, const unsigned int height, pointPairs* points)
	: m_plotPosX{ posX }
	, m_plotPosY{ posY }
	, m_plotWidth{ width }
	, m_plotHeight{ height }
	, m_coordinates{ points }
{
	m_sprite.setPosition(m_plotPosX, m_plotPosY);

	//image.create(m_plotWidth, m_plotHeight, sf::Color::Green);
	//m_plot.update(image);

	m_sprite.setColor(sf::Color::Blue);
}

Plotter::~Plotter()
{
}

const void Plotter::printCoordinates() const
{
	if (m_coordinates != nullptr)
		for (size_t i{ 0 }; i < m_coordinates->size(); ++i)
		{
			std::cout << std::fixed << m_coordinates->at(i).first << " | " << m_coordinates->at(i).second << std::endl;
		}
}

void Plotter::render(sf::RenderTarget& target)
{
	target.draw(m_sprite);
}

void Plotter::init()
{
	
}
