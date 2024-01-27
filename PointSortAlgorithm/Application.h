#ifndef APPLICATION_H
#define APPLICATION_H

#include "Conversion.h"
#include "Plotter.h"

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
	sf::View* m_view;
	Conversion m_converter;
	Plotter* m_plot;

	pointPairs m_points;

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

	//Helper
	inline float percentagePosX(const sf::VideoMode& vm, const float p) { return std::floor(static_cast<float>(vm.width) * (p / 100)); }
	inline float percentagePosY(const sf::VideoMode& vm, const float p) { return std::floor(static_cast<float>(vm.height) * (p / 100)); }
	inline float percentageSizeWidth(const sf::VideoMode& vm, const float p) { return std::floor(static_cast<float>(vm.width) * (p / 100)); }
	inline float percentageSizeHeight(const sf::VideoMode& vm, const float p) { return std::floor(static_cast<float>(vm.height) * (p / 100)); }
	inline unsigned int calculateCharSize(const sf::VideoMode& vm, const unsigned int mod) { return static_cast<unsigned int>((vm.width + vm.height) / mod); }

	/*
	const char* percentageBasedResultX(unsigned posX)
	{
		std::stringstream ss;
		ss << std::to_string(percentagePosX(posX)) << "%";
		std::string s{ ss.str() };
		std::cout << s.c_str() << std::endl;
		return s.c_str();
	}

	const char* percentageBasedResultY(unsigned posY)
	{
		std::stringstream ss;
		ss << std::to_string(percentagePosY(posY)) << "%";
		std::string s{ ss.str() };
		std::cout << s.c_str() << std::endl;
		return s.c_str();
	}

	const char* percentageBasedResultWidth(unsigned width)
	{
		std::stringstream ss;
		ss << std::to_string(percentageSizeWidth(width)) << "%";
		std::string s{ ss.str() };
		std::cout << s.c_str() << std::endl;
		return s.c_str();
	}

	const char* percentageBasedResultHeight(unsigned height)
	{
		std::stringstream ss;
		ss << std::to_string(percentageSizeHeight(height)) << "%";
		std::string s{ ss.str() };
		std::cout << s.c_str() << std::endl;
		return s.c_str();
	}
	*/
	//Master functions
	void masterEventHandler(tgui::Gui& gui);
	void masterUpdate();
	void masterRender(sf::RenderTarget& target, tgui::Gui& gui);

	//
	void displayPreview(tgui::TextArea::Ptr& previewArea);
};

#endif // !APPLICATION_H
