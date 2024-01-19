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
	tgui::MenuBar::Ptr m_menuBar;
	tgui::EditBox::Ptr m_inputFilePath;
	tgui::EditBox::Ptr m_outputFilePath;
	tgui::Button::Ptr m_buttonFile;
	tgui::Button::Ptr m_buttonCalc;
	tgui::Button::Ptr m_buttonSelect;
	tgui::Button::Ptr m_buttonSave;
	tgui::FileDialog::Ptr m_fileDialog;
	tgui::FileDialog::Ptr m_saveFileDialog;
	tgui::Label::Ptr m_labelError;
	tgui::TextArea::Ptr m_textAreaPreview;
	tgui::CheckBox::Ptr m_checkPreview;


	//private members;
	std::string m_openFilePath;
	std::string m_outFilePath;
	bool m_preview{ true };

	//Initializers
	void initGUI(tgui::MenuBar::Ptr& menuBar
		, tgui::EditBox::Ptr& inputFilePath
		, tgui::EditBox::Ptr& outputFilePath
		, tgui::Button::Ptr& buttonFile
		, tgui::Button::Ptr& buttonCalc
		, tgui::Button::Ptr& buttonSelect
		, tgui::Button::Ptr& buttonSave
		, tgui::FileDialog::Ptr& fileDialog
		, tgui::FileDialog::Ptr& saveFileDialog
		, tgui::Label::Ptr& labelError
		, tgui::TextArea::Ptr& textAreaPreview
		, tgui::CheckBox::Ptr& checkPreview
	);

	//Master functions
	void masterEventHandler(tgui::Gui& gui);
	void masterUpdate();
	void masterRender(sf::RenderTarget& target, tgui::Gui& gui);
};

#endif // !APPLICATION_H
