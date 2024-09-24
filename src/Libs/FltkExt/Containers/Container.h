#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Group.H>
#include "Libs/FltkExt/Containers/Margin.h"
#include "Libs/FltkExt/Containers/ContainerProps.h"
#include <memory>
#include <vector>


class Container : public Fl_Group
{
public:
	Container(int cx, int cy, int cw, int ch);

	void RecalcLayout(bool set = true);

	void resize(int cx, int cy, int cw, int ch) override;

	void draw() override;

	virtual void end();

protected:

	virtual void AdjustLayout(int cx, int cy, int cw, int ch);

private:
	bool _needRecalculate = false;
};

class ContainerEnd
{
public:
	ContainerEnd() {
		auto current = (Container*)Fl_Group::current();
		current->end();
	}
};
