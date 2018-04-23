#pragma once

#include <vector>
#include <string>
#include <variant>
#include <queue>
#include <set>

#include "Token.h"
#include "TokenStream.h"

class Tokenizer {
public:
	TokenStream getTokensList(const std::string& source);

private:
	Token getNumber(const std::string& source, int& ptrPos);
	Token getString(const std::string& source, int& ptrPos);
	std::string getIdentifier(const std::string& source, int& ptrPos);

	template<typename T>
	Token createToken(TokenType type, T value);

private:
	static std::set<std::string> m_keywords;
	static std::set<std::string> m_operations;
};