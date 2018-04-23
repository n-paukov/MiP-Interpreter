#pragma once

#include "StatementNode.h"
#include "ExpressionNode.h"

class WhileStatementNode : public StatementNode {
public:
	WhileStatementNode(ExpressionNode* expression, StatementNode* doNode)
		: m_expression(expression), m_do(doNode)
	{

	}

	virtual void execute() {
		PasValue value = m_expression->calculate();

		if (value.type != PasValue::Type::Boolean)
			throw std::exception("Wrong if expression type");

		while (std::get<bool>(value.value) == true) {
			m_do->execute();

			value = m_expression->calculate();
		}
	}

	virtual void regulateTree() {
		m_expression->setParentBlock(m_parentBlock);
		m_expression->regulateTree();

		m_do->setParentBlock(m_parentBlock);
		m_do->regulateTree();
	}

protected:
	ExpressionNode* m_expression;
	StatementNode* m_do;
};