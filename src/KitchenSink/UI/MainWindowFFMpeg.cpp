#include "MainWindowFFMpeg.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>


MainWindowFFMpeg::MainWindowFFMpeg(const char* label)
	: Fl_Double_Window(800, 600, label)
{
	auto fl = new Flex{ 0, 0, w(), h(), Direction::Vert };
	fl->margin(Margin{ 20 });
	fl->SetLayoutStrategy(LayoutStrategy::Full);
	{

		fl->end();
	}
}
