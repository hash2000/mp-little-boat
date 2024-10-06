#pragma once
#include "Libs/FltkExt/Data/IDataListener.h"

namespace FltkExt::Data
{
	class DataStore
	{
	public:

		void Append(Listener listener);

		void Remove(Listener listener);

		void SetProperties(const Props& props);

		void SetModel(const Model& model);

		const Model & GetModel() const;

		void AddRecord(const Rec& rec);

	private:

		std::list<Listener> _listeners;
		std::list<Rec> _records;

		Props _props;
		Model _model;
	};
}
