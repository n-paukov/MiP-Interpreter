#pragma once

#include <variant>

enum class TokenType {
	Bracket, Keyword, Identifier,
	IntNumber, RealNumber, Char, String, Punct, Operation
};

using TokenValue = std::variant<char, std::string, int, double>;

struct Token {
	TokenType type;
	TokenValue value;
};