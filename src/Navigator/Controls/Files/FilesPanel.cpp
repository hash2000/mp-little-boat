#include <pch.h>
#include "FilesPanel.h"
#include "FilesTable.h"
#include "FilesData.h"

FilesPanel::FilesPanel(int size, const char* l)
	: FltkExt::Containers::Panel(size, l)
{
	_table = std::make_shared<FilesTable>(0, 0, 0, 0);
	_data = std::make_unique<FilesData>();
	_data->AppendTable(_table);
}
