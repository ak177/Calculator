#pragma once

#include <functional>
#include <map>
#include <string>

#include "Lexer.hpp"
#include "Parser.hpp"

class Calculator {
public:
	Calculator();

	void run_file(const std::string& path);
	void run_cli();

private:
	void showIntro() const;
	bool handle_cmd(const std::string& cmd);
	void register_commands();

	Lexer::TokenStream tokenStream;
	Parser parser{ tokenStream };
	std::map<std::string, std::function<void()>> commands;
	bool isRunning{ true };
};

void print_complex(std::ostream& os, Complex num);