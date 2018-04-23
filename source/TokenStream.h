#pragma once

#include <deque>

#include "Token.h"

class TokenStream {
public:
	TokenStream();

	Token pop();
	const Token& front() const;

	void push(const Token& t);
	void push_front(const Token& t);

	size_t size() const;
	bool empty() const;
private:
	std::deque<Token> m_tokens;
};