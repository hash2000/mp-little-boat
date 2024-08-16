#pragma once

#include <streambuf>
#include <iostream>

class ProxyVectorStream : public std::iostream, private std::streambuf
{
private:
	std::vector<char>& _out;
public:
	ProxyVectorStream(std::vector<char>& out)
		: _out(out)
		, std::iostream(this)
	{
	}

	virtual std::streamsize xsputn(const char* s, std::streamsize n) override
	{
		_out.reserve(n);
		for (std::streamsize i = 0; i < n; i++) {
			_out.push_back(s[i]);
		}
		return n;
	}
};
