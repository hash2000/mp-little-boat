#pragma once
#include "Libs/FltkExt/Containers/Panel.h"
#include <memory>

class FilesTable;
class FilesData;


class FilesPanel : public FltkExt::Containers::Panel
{
public:
	FilesPanel(int size, const char* l);

private:

	std::shared_ptr<FilesTable> _table;
	std::unique_ptr<FilesData> _data;
};
