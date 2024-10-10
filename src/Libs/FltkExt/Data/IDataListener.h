#pragma once
#include "Libs/FltkExt/Data/DataRecord.h"

namespace FltkExt::Data
{
	struct IDataListener
	{
		virtual void ApplyProperties(const Props& props) = 0;

		virtual void ApplyModel(const Model& model) = 0;

		virtual void ApplyRecord(const Rec& rec) = 0;

		virtual void ClearRecodrs() = 0;
	};

}
