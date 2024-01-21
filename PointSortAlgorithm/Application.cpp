#include "stdafx.h"
#include "Application.h"

//Constructor
Application::Application()
{
	m_window = new sf::RenderWindow{ sf::VideoMode{static_cast<unsigned int>(800 * C_SCALE_FACTOR), static_cast<unsigned int>(600 * C_SCALE_FACTOR)}, "Coordinate Conversion", sf::Style::Titlebar | sf::Style::Close };
	initGUI(m_menuBar, m_inputFilePath, m_outputFilePath, m_buttonFile, m_buttonCalc, m_buttonSelect, m_buttonSave, m_fileDialog, m_saveFileDialog, m_labelError, m_textAreaPreview, m_checkPreview);
	m_plot = new Plotter{ 320, 210, static_cast<unsigned int>(470 * C_SCALE_FACTOR), static_cast<unsigned int>(280 * C_SCALE_FACTOR), &m_points };
}

//Destructor
Application::~Application()
{
	delete m_plot;
	delete m_window;
}

/// <summary>
/// Initialize the GUI elements
/// </summary>
/// <param name="textField">tgui::EditBox::Ptr : EditBox for the inputFile location</param>
/// <param name="button">tgui::Button::Ptr : Button to start the calculation process</param>
void Application::initGUI(
	tgui::MenuBar::Ptr& menuBar
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
	, tgui::CheckBox::Ptr& checkPreview)
{
	//Menu Bar
	menuBar = tgui::MenuBar::create();
	menuBar->addMenu("File");
	menuBar->addMenuItem("Load");
	menuBar->addMenuItem("Save");
	menuBar->addMenuItem("Exit");
	menuBar->addMenu("Edit");
	menuBar->addMenuItem("Calculate");

	menuBar->connectMenuItem("File", "Load", [&]() {
		fileDialog->setEnabled(true);
		fileDialog->setVisible(true);
		}
	);
	menuBar->connectMenuItem("File", "Save", [&]() {
		saveFileDialog->setEnabled(true);
		saveFileDialog->setVisible(true);
		}
	);
	menuBar->connectMenuItem("File", "Exit", [&]() { m_window->close(); });
	menuBar->connectMenuItem("Edit", "Calculate", [&]() { m_points = m_converter.calculate(m_openFilePath); });
	m_gui.add(menuBar);

	// Create TGUI inputFilePath textField
	inputFilePath = tgui::EditBox::create();
	inputFilePath->setPosition(110 * C_SCALE_FACTOR, 30 * C_SCALE_FACTOR);
	inputFilePath->setSize(680 * C_SCALE_FACTOR, 22 * C_SCALE_FACTOR);
	inputFilePath->setTextSize(13);
	inputFilePath->setDefaultText("Input filepath...");
	inputFilePath->setReadOnly(true);
	inputFilePath->setEnabled(false);
	m_gui.add(inputFilePath);

	// Create TGUI outputFilePath textField
	outputFilePath = tgui::EditBox::create();
	outputFilePath->setPosition(210 * C_SCALE_FACTOR, 90 * C_SCALE_FACTOR);
	outputFilePath->setSize(580 * C_SCALE_FACTOR, 22 * C_SCALE_FACTOR);
	outputFilePath->setTextSize(13);
	outputFilePath->setDefaultText("Output filepath...");
	outputFilePath->setReadOnly(true);
	outputFilePath->setEnabled(false);
	m_gui.add(outputFilePath);

	// Create Button for file selection
	buttonFile = tgui::Button::create();
	buttonFile->setPosition(10 * C_SCALE_FACTOR, 30 * C_SCALE_FACTOR);
	buttonFile->setSize(90 * C_SCALE_FACTOR, 22 * C_SCALE_FACTOR);
	buttonFile->setTextSize(13);
	buttonFile->setText("Select File");

	buttonFile->onPress([&]() {
		fileDialog->setEnabled(true);
		fileDialog->setVisible(true);
		}
	);

	m_gui.add(buttonFile);

	// Create a button to calculate the results
	buttonCalc = tgui::Button::create();
	buttonCalc->setPosition(10 * C_SCALE_FACTOR, 60 * C_SCALE_FACTOR);
	buttonCalc->setSize(90 * C_SCALE_FACTOR, 22 * C_SCALE_FACTOR);
	buttonCalc->setTextSize(13);
	buttonCalc->setText("Calculate!");

	buttonCalc->onPress([&]()
		{
			m_points = m_converter.calculate(m_openFilePath);
			labelError->setText("Calucalting done.");
			m_plot->printCoordinates();
			//displayPreview(textAreaPreview);
		}
	);

	m_gui.add(buttonCalc);

	// Create a button to calculate the results
	buttonSelect = tgui::Button::create();
	buttonSelect->setPosition(110 * C_SCALE_FACTOR, 90 * C_SCALE_FACTOR);
	buttonSelect->setSize(90 * C_SCALE_FACTOR, 22 * C_SCALE_FACTOR);
	buttonSelect->setTextSize(13);
	buttonSelect->setText("Select");

	buttonSelect->onPress([&]() {
		saveFileDialog->setEnabled(true);
		saveFileDialog->setVisible(true); }
	);

	m_gui.add(buttonSelect);

	// Create a button to save the converted pairs
	buttonSave = tgui::Button::create();
	buttonSave->setPosition(10 * C_SCALE_FACTOR, 90 * C_SCALE_FACTOR);
	buttonSave->setSize(90 * C_SCALE_FACTOR, 22 * C_SCALE_FACTOR);
	buttonSave->setTextSize(13);
	buttonSave->setText("Save");

	buttonSave->onPress([&]() {
		m_converter.saveToFile(m_outFilePath); labelError->setText("Saved to output file"); }
	);

	m_gui.add(buttonSave);

	//File Dialog
	fileDialog = tgui::FileDialog::create();
	fileDialog->setPosition(0, 0);
	fileDialog->setEnabled(false);
	fileDialog->setVisible(false);

	fileDialog->onFileSelect([&]() {
		m_openFilePath = fileDialog->getSelectedPaths()[0].asString().toStdString();
		inputFilePath->setText(m_openFilePath);
		}
	);

	m_gui.add(fileDialog);

	//Save file Dialog
	saveFileDialog = tgui::FileDialog::create();
	saveFileDialog->setPosition(0, 0);
	saveFileDialog->setEnabled(false);
	saveFileDialog->setVisible(false);

	saveFileDialog->onFileSelect([&]() {
		m_outFilePath = saveFileDialog->getSelectedPaths()[0].asString().toStdString();
		outputFilePath->setText(m_outFilePath);
		}
	);

	m_gui.add(saveFileDialog);

	//label
	labelError = tgui::Label::create();
	labelError->setPosition(220 * C_SCALE_FACTOR, 60 * C_SCALE_FACTOR);
	labelError->setSize(570 * C_SCALE_FACTOR, 22 * C_SCALE_FACTOR);
	labelError->setTextSize(13);
	labelError->setText("");
	labelError->setScrollbarPolicy(tgui::Scrollbar::Policy::Never);
	labelError->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	m_gui.add(labelError);

	//textarea
	textAreaPreview = tgui::TextArea::create();
	textAreaPreview->setPosition(10 * C_SCALE_FACTOR, 120 * C_SCALE_FACTOR);
	textAreaPreview->setSize(298 * C_SCALE_FACTOR, 465 * C_SCALE_FACTOR);
	textAreaPreview->setTextSize(13);
	textAreaPreview->setDefaultText("Preview");
	textAreaPreview->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
	textAreaPreview->setReadOnly(true);
	m_gui.add(textAreaPreview);

	//checkBox
	checkPreview = tgui::CheckBox::create();
	checkPreview->setPosition(110 * C_SCALE_FACTOR, 60 * C_SCALE_FACTOR);
	checkPreview->setSize(22 * C_SCALE_FACTOR, 22 * C_SCALE_FACTOR);
	checkPreview->setTextSize(13);
	checkPreview->setText("Preview?");
	checkPreview->setTextClickable(false);
	checkPreview->setChecked(true);
	m_gui.add(checkPreview);

	checkPreview->onClick([&]() { m_preview = !m_preview; });
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
	m_window->clear(sf::Color::White);

	gui.setTarget(target);
	gui.draw();
	m_plot->render(target);

	m_window->display();
}

void Application::displayPreview(tgui::TextArea::Ptr& previewArea)
{
	//BUGGED, DO NOT USE
	previewArea->setText('\n');
	for (size_t i{ 0 }; i < m_points.size(); ++i)
	{
		previewArea->addText(m_points.at(i).first.str());
		previewArea->addText(" | ");
		previewArea->addText(m_points.at(i).second.str());
	}
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
