#include "stdafx.h"
#include "Application.h"

//Constructor
Application::Application()
{
	m_window = new sf::RenderWindow{ sf::VideoMode{800, 600}, "Coordinate Conversion", sf::Style::Titlebar | sf::Style::Close };
	initGUI(m_textField, m_button);
}

//Destructor
Application::~Application()
{
	delete m_window;
}

/// <summary>
/// Initialize the GUI elements
/// </summary>
/// <param name="textField">tgui::EditBox::Ptr : EditBox for the inputFile location</param>
/// <param name="button">tgui::Button::Ptr : Button to start the calculation process</param>
void Application::initGUI(tgui::EditBox::Ptr& textField, tgui::Button::Ptr& button)
{
	// Create TGUI text field
	textField = tgui::EditBox::create();
	textField->setPosition(300, 250);
	textField->setSize(200, 30);
	textField->setDefaultText("Type something...");

	// Create a button to retrieve the text from the text field
	button = tgui::Button::create();
	button->setPosition(300, 300);
	button->setText("Get Text");

	// Callback function for the button
	button->onPress([&]() {
		auto& text = textField->getText();
		std::cout << "Text in the TextField: " << text.toStdString() << std::endl;
		m_converter.calculate(text.toStdString());
		});

	// Add the text field and button to the TGUI GUI
	m_gui.add(textField);
	m_gui.add(button);
}

/// <summary>
/// masterEventHandler, calls other eventHandling functions
/// </summary>
/// <param name="gui">tgui::Gui : GUI handle</param>
void Application::masterEventHandler(tgui::Gui& gui)
{
	sf::Event ev;
	while (m_window->pollEvent(ev))
	{
		gui.handleEvent(ev);
		switch (ev.type)
		{
		case sf::Event::Closed:
			m_window->close();
			break;
		case sf::Event::KeyPressed:
			switch (ev.key.code)
			{
			case sf::Keyboard::Key::Escape:
				m_window->close();
				break;
			}
		}
	}
}

/// <summary>
/// masterUpdate function, calls other update functions
/// </summary>
void Application::masterUpdate()
{
	masterEventHandler(m_gui);
}

/// <summary>
/// masterRender function, calls other render functions
/// </summary>
/// <param name="target">sf::RenderTarget : target to whichthe content will get rendered</param>
/// <param name="gui">tgui::Gui : GUI handle</param>
void Application::masterRender(sf::RenderTarget& target, tgui::Gui& gui)
{
	m_window->clear(sf::Color::Blue);

	gui.setTarget(target);
	gui.draw();

	m_window->display();
}

/// <summary>
/// Loop that runs the Application
/// </summary>
void  Application::appLoop()
{
	while (m_window->isOpen())
	{
		masterUpdate();
		masterRender(*m_window, m_gui);
	}
}
