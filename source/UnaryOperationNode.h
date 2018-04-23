#pragma once

#include <string>
#include "ExpressionNode.h"

class UnaryOperationNode : public ExpressionNode {
public:
	UnaryOperationNode(ExpressionNode* operand, std::string operation)
		: m_operand(operand), m_operation(operation) {

	}

	virtual PasValue calculate() {
		PasValue opValue = m_operand->calculate();

		if (m_operation == "-")
			return -opValue;
		else if (m_operation == "not")
			return !opValue;
	
		return opValue;
	}

	virtual void regulateTree() {
		m_operand->setParentBlock(m_parentBlock);
		m_operand->regulateTree();
	}

protected:
	ExpressionNode* m_operand;
	std::string m_operation;
};