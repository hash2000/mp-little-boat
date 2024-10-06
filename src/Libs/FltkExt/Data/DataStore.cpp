#include "DataStore.h"

namespace FltkExt::Data
{
	void DataStore::Append(Listener listener)
	{
		_listeners.push_back(listener);
	}

	void DataStore::Remove(Listener listener)
	{
		for (auto item = _listeners.begin(); item != _listeners.end(); item++)
		{
			auto pListener = *item;
			if (pListener == listener) {
				_listeners.erase(item);
				break;
			}
		}
	}

	void DataStore::SetProperties(const Props& props)
	{
		_props = props;

		for (auto list : _listeners) {
			list->ApplyProperties(_props);
		}
	}

	void DataStore::SetModel(const Model& model)
	{
		_model = model;

		for (auto list : _listeners) {
			list->ApplyModel(_model);
		}
	}

	const Model & DataStore::GetModel() const
	{
		return _model;
	}

	void DataStore::AddRecord(const Rec& rec)
	{
		_records.push_back(rec);

		for (auto list : _listeners) {
			list->ApplyRecord(rec);
		}
	}

}
