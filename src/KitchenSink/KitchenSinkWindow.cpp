#include "KitchenSinkWindow.h"
#include "KitchenSink/UI/MainWindowFlex.h"
#include "KitchenSink/UI/MainWindowPanel.h"
#include "KitchenSink/UI/MainWindowFltkTable.h"
#include "KitchenSink/UI/MainWindowFltkTextBuffer.h"
#include "KitchenSink/UI/MainWindowFltkTextEditor.h"
#include "KitchenSink/UI/MainWindowFltkThemes.h"
#include "KitchenSink/UI/MainWindowFltkSlider.h"
#include "KitchenSink/UI/MainWindowFltkTreeOfTables.h"
#include "KitchenSink/UI/MainWindowFltkTree.h"
#include "KitchenSink/UI/MainWindowGrid.h"
#include "KitchenSink/UI/MainWindowList.h"
#include "KitchenSink/UI/MainWindowDataTable.h"
#include "KitchenSink/UI/MainWindowPickers.h"
#include <Poco/String.h>
#include <Poco/StringTokenizer.h>

KitchenSinkWindow::KitchenSinkWindow()
	: Fl_Double_Window(800, 600, "KitchenSink")
{
	_currentSample = std::make_unique<CurrentSample>();

	_layout = std::make_unique<Layout>(0, 0, w(), h());
	{
		_leftPanel = std::make_unique<Panel>(300, "Samples");
		_leftPanel->UseHideButton(false);
		_leftPanel->UsePinButton(false);
		{
			CreateSamplesTree();
			PopulateSamplesTree();
			_leftPanel->end();
		}


		_centerPanel = std::make_unique<Panel>(200, nullptr);
		_centerPanel->UseHeader(false);
		_centerPanel->UseHideButton(false);
		_centerPanel->UsePinButton(false);
		{

			_centerPanel->end();
		}

		_layout->Attach(_leftPanel.get(), Docking::Left);
		_layout->Attach(_centerPanel.get(), Docking::Center);
		_layout->end();
	}
}

void KitchenSinkWindow::CreateSamplesTree()
{
	_samplesTree = std::make_unique<Fl_Tree>(0, 0, 0, 0);
	_samplesTree->color(FL_BACKGROUND_COLOR);
	_samplesTree->color2(FL_BACKGROUND_COLOR);
	_samplesTree->showroot(0);
	_samplesTree->callback([](Fl_Widget* widget, void* data)
		{
			auto me = (Fl_Tree*)widget;
			auto window = (KitchenSinkWindow*)data;
			auto item = (Fl_Tree_Item*)me->callback_item();
			if (!item) {
				return;
			}

			auto reason = me->callback_reason();
			switch (reason) {
			case FL_TREE_REASON_SELECTED:
			{
				std::string pathname;
				pathname.resize(256);
				me->item_pathname(&pathname[0], sizeof(pathname), item);
				window->RunSample(pathname);
			}
			}

		}, this);
}

void KitchenSinkWindow::PopulateSamplesTree()
{
	_samplesTree->add("fltk/Slider");
	_samplesTree->add("fltk/Table");
	_samplesTree->add("fltk/TextBuffer");
	_samplesTree->add("fltk/TextEditor");
	_samplesTree->add("fltk/Themes");
	_samplesTree->add("fltk/Trees/Tree");
	_samplesTree->add("fltk/Trees/TreeOfTables");
	_samplesTree->add("fltkext/Containers/Flex");
	_samplesTree->add("fltkext/Containers/List");
	_samplesTree->add("fltkext/Containers/Panels");
	_samplesTree->add("fltkext/Controls/Pickers");
}

void KitchenSinkWindow::RunSample(const std::string& name)
{
	if (!_currentSample || _currentSample->_name == name) {
		return;
	}

	CloseCurrentSample();

	auto trimName = name;
	auto tromNameLen = std::strlen(trimName.c_str());
	trimName.resize(tromNameLen);

	if (trimName == "fltk/Slider") {
		_currentSample->CreateSample<MainWindowFltkSlider>(name);
	}
	else if (trimName == "fltk/Table") {
		_currentSample->CreateSample<MainWindowFltkTable>(name);
	}
	else if (trimName == "fltk/TextBuffer") {
		_currentSample->CreateSample<MainWindowFltkTextBuffer>(name);
	}
	else if (trimName == "fltk/TextEditor") {
		_currentSample->CreateSample<MainWindowFltkTextEditor>(name);
	}
	else if (trimName == "fltk/Themes") {
		_currentSample->CreateSample<MainWindowFltkThemes>(name);
	}
	else if (trimName == "fltk/Trees/Tree") {
		_currentSample->CreateSample<MainWindowFltkTree>(name);
	}
	else if (trimName == "fltk/Trees/TreeOfTables") {
		_currentSample->CreateSample<MainWindowFltkTreeOfTables>(name);
	}
	else if (trimName == "fltkext/Containers/Flex") {
		_currentSample->CreateSample<MainWindowFlex>(name);
	}
	else if (trimName == "fltkext/Containers/List") {
		_currentSample->CreateSample<MainWindowList>(name);
	}
	else if (trimName == "fltkext/Containers/Panels") {
		_currentSample->CreateSample<MainWindowPanel>(name);
	}
	else if (trimName == "fltkext/Controls/Pickers") {
		_currentSample->CreateSample<MainWindowPickers>(name);
	}

}

void KitchenSinkWindow::CloseCurrentSample()
{
	if (!_currentSample) {
		return;
	}

	_currentSample->_name.clear();
}
