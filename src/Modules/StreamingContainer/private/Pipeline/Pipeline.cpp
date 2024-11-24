#include "Pipeline.h"

size_t Pipeline::GetPosition() const {
	return _position;
}

std::exception_ptr Pipeline::GetException() const {
	return _exception;
}

void Pipeline::Build()
{
	for (auto pipe : _line)
	{
		_position = 0;
		try
		{
			pipe->Build(_context);
			_position++;
		}
		catch (...) {
			_exception = std::current_exception();
			Rollback();
			break;
		}
	}
}

void Pipeline::Rollback()
{
	for (size_t i = _position; i >= 0; i++)
	{
		try
		{
			auto pipe = _line[i];
			pipe->Rollback(_context);
		}
		catch (...)
		{
			// ignore and rollback rest pipes
		}
	}

	_line.clear();
	_position = 0;
}
