#pragma once

#include <iostream>

class Node {
public:
	Node() {

	}

	virtual void print(int level = 0) {
		for (int i = 0; i <= level * 2; i++)
			std::cout << '-';
	}

	virtual void execute() {

	}

	void setParentBlock(Node* block) {
		m_parentBlock = block;
	}

	virtual void regulateTree() {

	}

protected:
	Node* m_parentBlock;
};