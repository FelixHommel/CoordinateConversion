#ifndef APPLICATION_H
#define APPLICATION_H

#include "Conversion.h"

class Application
{
public:
	//Constructor / Destructor
	Application();
	~Application();

	//Public functions
	void appLoop();

private:
	//Private members
	sf::RenderWindow* m_window;
	Conversion m_converter;

	//GUI elements
	tgui::Gui m_gui;
	tgui::EditBox::Ptr m_textField;
	tgui::Button::Ptr m_button;

	//Initializers
	void initGUI(tgui::EditBox::Ptr& tf, tgui::Button::Ptr& btn);

	//Master functions
	void masterEventHandler(tgui::Gui& gui);
	void masterUpdate();
	void masterRender(sf::RenderTarget& target, tgui::Gui& gui);
};

#endif // !APPLICATION_H
