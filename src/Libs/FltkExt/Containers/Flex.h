#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <memory>
#include <vector>

class Flex : public Fl_Group
{
public:
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

	Flex(int cx, int cy, int cw, int ch, Direction direction, PushPosition position, Docking docking = Docking::ByDirection, int spacing = 0);

	void RecalcLayout(bool set = true);

	void resize(int cx, int cy, int cw, int ch) override;

	void draw() override;

	virtual void end();

private:
	void InitElementsContext();

	void AdjustMainSizes(int cx, int cy, int cw, int ch);

	void AdjustLayout(int cx, int cy, int cw, int ch);

private:
	bool _needRecalculate = false;
	Direction _direction;
	PushPosition _position;
	Docking _docking;
	int _size;
	int _spacing = 0;

private:
	struct ElementContext {
		int width = 0;
		int height = 0;
	};

	std::vector<std::shared_ptr<ElementContext>> _elements;
};

class FlexEnd
{
public:
	FlexEnd() {
		auto current = (Flex*)Fl_Group::current();
		current->end();
	}
};
