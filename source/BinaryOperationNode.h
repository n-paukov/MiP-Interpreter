#pragma once

#include <string>
#include "ExpressionNode.h"

class BinaryOperationNode : public ExpressionNode {
public:
	BinaryOperationNode() {

	}

	BinaryOperationNode(ExpressionNode* left, std::string operation, ExpressionNode* right)
		: m_left(left), m_operation(operation), m_right(right) {
		
	}

	~BinaryOperationNode() {
		delete m_left;
		delete m_right;
	}

	virtual PasValue calculate() {
		PasValue left = m_left->calculate();
		PasValue right = m_right->calculate();

		if (m_operation == "+")
			return left + right;
		else if (m_operation == "-")
			return left - right;
		else if (m_operation == "*")
			return left * right;
		else if (m_operation == "and")
			return left && right;
		else if (m_operation == "or")
			return left || right;
		else if (m_operation == "=")
			return left == right;
		else if (m_operation == ">")
			return left > right;
		else if (m_operation == ">=")
			return left >= right;
		else if (m_operation == "<")
			return left < right;
		else if (m_operation == "<=")
			return left <= right;
		else if (m_operation == "<>")
			return left != right;

		throw std::exception("Unknown operation");
	}

	virtual void regulateTree() {
		m_left->setParentBlock(m_parentBlock);
		m_left->regulateTree();

		m_right->setParentBlock(m_parentBlock);
		m_right->regulateTree();
	}

protected:
	ExpressionNode* m_left;
	std::string m_operation;
	ExpressionNode* m_right;
};