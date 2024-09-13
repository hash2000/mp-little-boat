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
	Container(int cx, int cy, int cw, int ch, Direction direction, PushPosition position = PushPosition::Start);

	PushPosition GetPushPosition() const;

	void SetPushPosition(PushPosition pos);

	Direction direction() const;

	void direction(Direction dir);

	LayoutStrategy GetLayoutStrategy() const;

	void SetLayoutStrategy(LayoutStrategy set);

	const Margin& margin() const;

	void margin(const Margin& m);

	void RecalcLayout(bool set = true);

	void resize(int cx, int cy, int cw, int ch) override;

	void draw() override;

	virtual void end();

protected:

	virtual void AdjustLayout(int cx, int cy, int cw, int ch) = 0;

	void AdjustMainSizes(int cx, int cy, int cw, int ch);

	void BeginLayout();

	void EndLayout();

private:
	bool _needRecalculate = false;

protected:
	Direction _direction;
	PushPosition _position;
	LayoutStrategy _layoutStraategy;
	Margin _margin;
	int _size;

protected:
	struct ElementContext {
		int width = 0;
		int height = 0;
	};

	std::vector<std::shared_ptr<ElementContext>> _elements;
};

class ContainerEnd
{
public:
	ContainerEnd() {
		auto current = (Container*)Fl_Group::current();
		current->end();
	}
};
