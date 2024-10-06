#pragma once
#include <Poco/Any.h>
#include <Poco/Dynamic/Var.h>
#include <memory>
#include <list>
#include <map>
#include <string>

namespace FltkExt::Data
{
	struct IDataListener;

	using Listener = std::shared_ptr<IDataListener>;
	using Var = Poco::Dynamic::Var;
	using Rec = std::map<std::string, Var>;
	using Model = std::list<Rec>;
	using Props = Rec;

	template<class T> T GetRecValue(const Rec& rec, const std::string& name, T defaultValu) {
		Rec::const_iterator it;
		if ((it = rec.find(name)) != rec.end() && it->second.type() == typeid(T)) {
			return it->second.convert<T>();
		}
		return defaultValu;
	}

	template <class T = Model::const_iterator> T GetModelField(const Model& model, const std::string& name, const std::string& value) {
		for (auto i = model.begin(); i != model.end(); i++) {
			auto it = *i;
			Rec::const_iterator field;
			if ((field = it.find(name)) != it.end() && field->second == value) {
				return i;
			}
		}
		return model.end();
	}

	struct IDataListener
	{
		virtual void ApplyProperties(const Props& props) = 0;

		virtual void ApplyModel(const Model& model) = 0;

		virtual void ApplyRecord(const Rec& rec) = 0;
	};

}
