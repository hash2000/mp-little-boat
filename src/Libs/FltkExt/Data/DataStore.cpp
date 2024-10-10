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

		auto records = _records;
		ClearRecodrs();

		for (auto list : _listeners) {
			list->ApplyModel(_model);
		}

		for (auto rec : records) {
			Rec newRec;
			ReorderRecordModel(rec, newRec);
			AddRecord(newRec);
			_records.push_back(newRec);
		}
	}

	const Model& DataStore::GetModel() const
	{
		return _model;
	}

	void DataStore::ReorderRecordModel(const Rec& rec, Rec& newRec)
	{
		for (auto item : _model)
		{
			auto name = item.GetValue<std::string>("field", std::string());
			if (name.size() == 0) {
				continue;
			}

			auto recIt = rec.FindField(name);
			if (recIt == rec.end()) {
				continue;
			}

			newRec.push_back(*recIt);
		}
	}

	void DataStore::AddRecord(const Rec& rec)
	{
		Rec newRec;
		ReorderRecordModel(rec, newRec);

		_records.push_back(newRec);

		for (auto list : _listeners) {
			list->ApplyRecord(newRec);
		}
	}

	void DataStore::ClearRecodrs()
	{
		_records.clear();
		for (auto list : _listeners) {
			list->ClearRecodrs();
		}
	}
}
