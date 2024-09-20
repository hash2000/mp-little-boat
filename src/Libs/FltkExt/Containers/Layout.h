#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include "Libs/FltkExt/Containers/Container.h"
#include "Libs/FltkExt/Containers/ContainerProps.h"
#include <unordered_map>
#include <list>
#include <memory>

class Panel;
class Layout : public Container
{
public:
	Layout(int cx, int cy, int cw, int ch);

	void AttachPanel(Panel& p, Docking docking);

	void AttachPanel(Panel* p, Docking docking);

	void DetachPanel(Panel* p);

	bool HasPanel(const Panel* p) const;

protected:

	void AdjustLayout(int cx, int cy, int cw, int ch);

private:

	std::unordered_map<Docking, std::list<Panel*>> _panelDocking;

	Panel* _centerPanel = nullptr;
};
