#pragma once

#include <complex>
#include <istream>
#include <map>
#include <string>
#include <sstream>

#include "Lexer.hpp"
#include "SymbolTable.hpp"

using Complex = std::complex<double>;

class ErrorReporter {
public:
	template<class T, class ...Args>
	void operator()(const T& t, Args&&... args)
	{
		error(t, std::forward<Args>(args)...);
	}

private:
	template<class T, class ...Args>
	void error(const T& t, Args&&... args)
	{
		msgStream << t;
		error(std::forward<Args>(args)...);
	}

	void error()
	{
		auto msg = msgStream.str();
		msgStream.clear();
		throw std::runtime_error{ msg };
	}

	std::ostringstream msgStream;
};

class Parser {
public:
	explicit Parser(Lexer::TokenStream& lexer);

	void parse();
	void parse(const std::string& input);
	Complex result() const { return res; }
	SymbolTable& symbol_table() { return table; }

private:
	Complex expr();
	Complex term();
	Complex postfix();
	Complex prim();

	bool consume(Kind kind);
	bool peek(Kind kind) const;
	void expect(Kind kind);

	void check_all_paren_closed();
	void check_open_paren();
	void consume_closing_paren();

	Token prevToken;
	SymbolTable table;
	Lexer::TokenStream& ts;
	int lparenCount{};
	Complex res;
	ErrorReporter error;
};

Complex safe_div(Complex left, Complex right);
Complex safe_floordiv(Complex left, Complex right);
template<class T>
T safe_mod(T left, T right)
{
	if (right) {
		return left % right;
	}
	throw std::runtime_error{ "Divide by Zero" };
}
unsigned factorial(int n);
