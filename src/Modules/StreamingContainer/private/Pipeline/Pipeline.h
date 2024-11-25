#pragma once
#include "Pipe.h"
#include <vector>
#include <memory>
#include <utility>
#include <exception>

class Pipeline
{
public:
	template<class T, class... TArgs> void Add(TArgs&&... arguments) {
		auto instance = std::make_shared<T>(std::forward<TArgs>(arguments)...);
		_line.push_back(instance);
	}

	size_t GetPosition() const;

	std::exception_ptr GetException() const;

	PipeContext& GetContext();

	void Build();

	void Rollback();

private:
	std::exception_ptr _exception;
	std::vector<std::shared_ptr<Pipe>> _line;
	size_t _position = 0;
	PipeContext _context;
};
