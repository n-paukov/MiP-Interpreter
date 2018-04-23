#include "Tokenizer.h"

std::set<std::string> Tokenizer::m_keywords{
	"div", "if", "then", "else", "of",
	"while", "do", "begin", "end", "read", "write", "var", "array",
	"procedure", "program"
};

std::set<std::string> Tokenizer::m_operations{
	"or", "and", "not", "div"
};

TokenStream Tokenizer::getTokensList(const std::string& source) {
	int ptrPos = 0;
	int length = source.length();

	TokenStream tokens;

	while (ptrPos < length) {
		char ch = source[ptrPos];

		if (isdigit(ch))
			tokens.push(getNumber(source, ptrPos));
		else if (ch == '\'') {
			ptrPos++;
			tokens.push(getString(source, ptrPos));
		}
		else if (isalpha(ch) || ch == '_') {
			std::string identifier = getIdentifier(source, ptrPos);

			if (m_keywords.find(identifier) != m_keywords.end())
				tokens.push(createToken(TokenType::Keyword, identifier));
			else if (m_operations.find(identifier) != m_operations.end())
				tokens.push(createToken(TokenType::Operation, identifier));
			else
				tokens.push(createToken(TokenType::Identifier, identifier));
		}
		else if (ptrPos < length - 1 && ((ch == ':' && source[ptrPos + 1] == '=') || (ch == '<' && source[ptrPos + 1] == '=')
			|| (ch == '>' && source[ptrPos + 1] == '=') || (ch == '<' && source[ptrPos + 1] == '>')
			))
		{
			std::string op;
			op.push_back(ch);
			op.push_back(source[ptrPos + 1]);

			tokens.push(createToken(TokenType::Operation, op));

			ptrPos += 2;
		}
		else if (ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '=' || ch == '<' || ch == '>') {
			std::string op;
			op.push_back(ch);
			tokens.push(createToken(TokenType::Operation, op));
			ptrPos++;
		}
		else if (ch == '(' || ch == ')' || ch == '[' || ch == ']') {
			tokens.push(createToken(TokenType::Bracket, ch));
			ptrPos++;
		}
		else if (ch == ',' || ch == '.' || ch == ';' || ch == ':') {
			tokens.push(createToken(TokenType::Punct, ch));
			ptrPos++;
		}
		else if (isspace(ch)) {
			ptrPos++;
			continue;
		}
		else
			throw std::exception();
	}

	return tokens;
}

template<typename T>
Token Tokenizer::createToken(TokenType type, T value) {
	TokenValue v = value;

	return Token{ type, v };
}

Token Tokenizer::getNumber(const std::string& source, int& ptrPos) {
	std::string numText;

	int dotPos = -1;
	int currentPos = 0;

	while (isdigit(source[ptrPos]) || source[ptrPos] == '.') {
		if (source[ptrPos] == '.') {
			if (dotPos != -1)
				throw std::exception();

			numText.push_back(source[ptrPos]);

			ptrPos++;
			dotPos = currentPos;
		
			continue;
		}

		numText.push_back(source[ptrPos]);
		ptrPos++;
		currentPos++;
	}

	if (isalpha(source[ptrPos]))
		throw std::exception();

	if (dotPos != -1)
		return createToken(TokenType::RealNumber, std::stod(numText));

	return createToken(TokenType::IntNumber, std::stoi(numText));
}

Token Tokenizer::getString(const std::string& source, int& ptrPos) {
	std::string content = "";

	while (source[ptrPos] != '\'') {
		content.push_back(source[ptrPos++]);
	}

	ptrPos++;

	return createToken(TokenType::String, content);
}

std::string Tokenizer::getIdentifier(const std::string& source, int& ptrPos) {
	std::string identifier = "";
	
	while (isalpha(source[ptrPos]) || source[ptrPos] == '_' || isdigit(source[ptrPos])) {
		identifier.push_back(source[ptrPos++]);
	}

	return identifier;
}