#pragma once

#include <string>
#include "StatementNode.h"
#include "ExpressionNode.h"
#include "BlockNode.h"

class AssignmentNode : public StatementNode {
public:
	AssignmentNode(const std::string& variable, ExpressionNode* expression)
		: m_variable(variable), m_expression(expression) {
		
	}

	~AssignmentNode() {
		delete m_expression;
	}

	virtual void execute() {
		PasValue v = m_expression->calculate();

		if (static_cast<BlockNode*>(m_parentBlock)->m_variables[m_variable].type != v.type)
			throw std::exception("Wrong assignment");

		static_cast<BlockNode*>(m_parentBlock)->m_variables[m_variable].value = v;
	}

	virtual void regulateTree() {
		m_expression->setParentBlock(m_parentBlock);
		m_expression->regulateTree();
	}

protected:
	std::string m_variable;
	ExpressionNode* m_expression;
};