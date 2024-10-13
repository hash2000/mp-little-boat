#pragma once
#include <Poco/Any.h>
#include <Poco/Dynamic/Var.h>
#include <memory>
#include <list>
#include <unordered_map>
#include <string>
#include <utility>

namespace FltkExt::Data
{
	struct IDataListener;

	using Listener = std::shared_ptr<IDataListener>;
	using Var = Poco::Dynamic::Var;

	class Rec : public std::list<std::pair<std::string, Var>> {
	public:
		using list_type = std::pair<std::string, Var>;

		Rec() {
		}

		Rec(std::initializer_list<list_type> list)
			: std::list<list_type>(list) {
		}

		Rec(const std::list<list_type>& right)
			: std::list<list_type>(right) {
		}

		const_iterator FindField(const std::string& field) const {
			for (auto it = begin(); it != end(); it++) {
				if (it->first == field) {
					return it;
				}
			}
			return end();
		}

		template <class T>
		const T GetValue(const std::string& field, const T& defaultValue) const {
			const_iterator result;
			if ((result = FindField(field)) != end() && result->second.type() == typeid(T)) {
				return result->second.convert<T>();
			}
			return defaultValue;
		}
	};

	using Props = Rec;

	class Model : public std::list<Rec>
	{
	public:
		using list_type = Rec;

		Model() {
		}

		Model(std::initializer_list<list_type> list) : std::list<list_type>(list) {
		}

		const_iterator GetField(const std::string& name, const std::string& value) const {
			for (auto i = begin(); i != end(); i++) {
				auto it = *i;
				Rec::const_iterator record_field = it.FindField(name);
				if (record_field != it.end() && record_field->second == value) {
					return i;
				}
			}
			return end();
		}
	};

}
