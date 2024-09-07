#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include "Libs/FltkExt/Containers/Margin.h"
#include <memory>
#include <vector>

enum class Direction : int {
	Vert,
	Horz,
};

enum class PushPosition : int {
	Start,
	End,
};

enum class Docking : int {
	ByDirection,
	Full,
};

class Container : public Fl_Group
{
public:
	Container(int cx, int cy, int cw, int ch, Direction direction, PushPosition position = PushPosition::Start);

	Docking docking() const;

	void docking(Docking dock);

	Margin margin() const;

	void margin(const Margin& m);

	void RecalcLayout(bool set = true);

	void resize(int cx, int cy, int cw, int ch) override;

	void draw() override;

	virtual void end();

protected:

	virtual void AdjustLayout(int cx, int cy, int cw, int ch) = 0;

	void BeginLayout(int cx, int cy, int cw, int ch);

	void EndLayout();

private:
	void InitElementsContext();

	void AdjustMainSizes(int cx, int cy, int cw, int ch);

private:
	bool _needRecalculate = false;

protected:
	Direction _direction;
	PushPosition _position;
	Docking _docking;
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
