#include "../stdafx.h"
#include "../include/Plotter.h"

Plotter::Plotter(sf::RenderWindow* window, pointPairs* points)
	: m_coordinates{ points }
{
	plot = new sf::VertexArray{ sf::Points, m_coordinates->size() }; //Init vertexArray that it contains sf::Points and as many of that as therea are points in pointPairs
	addPoints2Vertex();
	drawPlot(window);
}

Plotter::~Plotter()
{
	delete plot;
}

void Plotter::drawPlot(sf::RenderTarget* window)
{
	
}

const void Plotter::printCoordinates() const
{
	if (m_coordinates != nullptr)
	{
		for (size_t i{ 0 }; i < m_coordinates->size(); ++i)
		{
			std::cout << std::fixed << m_coordinates->at(i).first << " | " << m_coordinates->at(i).second << std::endl;
		}
	}
	else
		std::cerr << "No Points to Print" << std::endl;
}

void Plotter::render(sf::RenderTarget& target)
{
	sf::Vertex xAxis[] =
	{
		sf::Vertex(sf::Vector2f(0.f, static_cast<float>(target.getSize().x / 2)), sf::Color::Black), // Start point
		sf::Vertex(sf::Vector2f(static_cast<float>(target.getSize().x), static_cast<float>(target.getSize().y / 2)), sf::Color::Black) // End point
	};

	sf::Vertex yAxis[] =
	{
		sf::Vertex(sf::Vector2f(static_cast<float>(target.getSize().x / 2), 0.f), sf::Color::Black), // Start point
		sf::Vertex(sf::Vector2f(static_cast<float>(target.getSize().x / 2), static_cast<float>(target.getSize().y)), sf::Color::Black) // End point
	};

	target.draw(xAxis, 2, sf::Lines);
	target.draw(yAxis, 2, sf::Lines);
	target.draw(*plot);
}

void Plotter::addPoints2Vertex()
{
	int index{ 0 };
	for (size_t i{ 0 }; i < m_coordinates->size(); ++i)
	{
		plot->append(sf::Vertex(sf::Vector2f{ static_cast<float>(m_coordinates->at(i).first) * 10, static_cast<float>(m_coordinates->at(i).second) * 10 }, sf::Color::Red));
	}
}
