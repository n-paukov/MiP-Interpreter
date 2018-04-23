#include "TokenStream.h"

TokenStream::TokenStream() {

}

Token TokenStream::pop() {
	if (empty())
		throw std::exception();

	Token t = m_tokens.front();

	m_tokens.pop_front();

	return t;
}

const Token& TokenStream::front() const {
	if (empty())
		throw std::exception();

	return m_tokens.front();
}

void TokenStream::push(const Token& t) {
	m_tokens.push_back(t);
}

void TokenStream::push_front(const Token& t) {
	m_tokens.push_front(t);
}

size_t TokenStream::size() const {
	return m_tokens.size();
}

bool TokenStream::empty() const {
	return m_tokens.empty();
}