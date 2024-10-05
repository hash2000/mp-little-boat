#include <pch.h>
#include "FilesData.h"

void FilesData::AppendTable(TablePtr table)
{
	_tables.push_back(table);
}

void FilesData::RemoveTable(TablePtr table)
{
	for (auto item = _tables.begin(); item != _tables.end(); item ++)
	{
		auto pTable = *item;
		if (pTable == table) {
			_tables.erase(item);
			break;
		}
	}
}
