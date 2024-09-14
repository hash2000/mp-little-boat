#pragma once
#include "Libs/FltkExt/Containers/Container.h"

class Flex : public Container
{
public:

	Flex(int cx, int cy, int cw, int ch, Direction direction, PushPosition position = PushPosition::Start);

	int spacing() const;

	void spacing(int size);

	PushPosition GetPushPosition() const;

	void SetPushPosition(PushPosition pos);

	Direction direction() const;

	void direction(Direction dir);

	LayoutStrategy GetLayoutStrategy() const;

	void SetLayoutStrategy(LayoutStrategy set);

	const Margin& margin() const;

	void margin(const Margin& m);

	void on_remove(int index) /* override включить в версии 1.4.0 */;

private:
	void AdjustLayout(int cx, int cy, int cw, int ch) override;

	void AdjustMainSizes(int cx, int cy, int cw, int ch);

	void BeginLayout();

	void EndLayout();

private:
	int _spacing = 0;
	Direction _direction;
	PushPosition _position;
	LayoutStrategy _layoutStraategy;
	Margin _margin;
	int _size;

	struct ElementContext {
		int width = 0;
		int height = 0;
	};

	std::vector<std::shared_ptr<ElementContext>> _elements;
};

