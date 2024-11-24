#include "MainWindowFFMpeg.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>


MainWindowFFMpeg::MainWindowFFMpeg(const char* label, const Ioc::Kernel& kernel)
	: Fl_Double_Window(800, 600, label)
{
	auto fl = new Flex{ 0, 0, w(), h(), Direction::Vert };
	fl->margin(Margin{ 20 });
	fl->SetLayoutStrategy(LayoutStrategy::Full);
	{
		auto btFlex = new Flex{ 40 , Direction::Horz };
		btFlex->margin(Margin{ 10 });
		btFlex->gap(10);
		{
			auto btBuffer = new Fl_Button(0, 0, 100, 22, "buffer");
			btBuffer->callback([](Fl_Widget* widget, void* data) {
				((MainWindowFFMpeg*)data)->OnBuffer((Fl_Button*)widget);
				}, this);

			btFlex->end();
		}

		fl->end();
	}
}

void MainWindowFFMpeg::OnBuffer(Fl_Button* widget)
{
	_stream = std::make_unique<Poco::FileStream>(_videoFile);
}
