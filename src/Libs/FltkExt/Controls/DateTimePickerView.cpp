#include "DateTimePickerView.h"

namespace FltkExt::Controls
{
	DateTimePickerView::DateTimePickerView(int cw, int ch)
		: Picker(cw, ch)
	{
		_mainFlex = std::make_shared<Flex>(0, 0, w(), h(), Direction::Vert);
		_mainFlex->SetLayoutStrategy(LayoutStrategy::Full);
		//_mainFlex->box(FL_FREE_BOXTYPE);
		//_mainFlex->color(fl_lighter(FL_RED));
		
	}

}

