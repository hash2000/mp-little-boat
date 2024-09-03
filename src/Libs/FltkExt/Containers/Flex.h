#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <memory>
#include <vector>

class Flex : public Fl_Group
{
public:
	enum {
		Vert,
		Horz,
	};

	enum {
		Start,
		End,
	};

	Flex(int direction, int pos, int size = 0, int spacing = 0);

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
	int _direction;
	int _position;
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
