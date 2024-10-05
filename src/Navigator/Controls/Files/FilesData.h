#pragma once
#include "Navigator/Controls/Files/FilesTable.h"
#include <list>
#include <memory>

class FilesData
{
public:
	using TablePtr = std::shared_ptr<FilesTable>;

public:

	void AppendTable(TablePtr table);

	void RemoveTable(TablePtr table);

private:

	std::list<TablePtr> _tables;

};
