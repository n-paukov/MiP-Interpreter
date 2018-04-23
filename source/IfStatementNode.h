#pragma once

#include <optional>

#include "StatementNode.h"
#include "ExpressionNode.h"

class IfStatementNode : public StatementNode {
public:
	IfStatementNode(ExpressionNode* expression, StatementNode* thenNode, StatementNode* elseNode)
		: m_expression(expression), m_then(thenNode), m_else(elseNode) 
	{

	}

	~IfStatementNode() {
		delete m_expression;
		delete m_then;
		delete m_else;
	}

	virtual void execute() {
		PasValue value = m_expression->calculate();

		if (value.type != PasValue::Type::Boolean)
			throw std::exception("Wrong if expression type");

		if (std::get<bool>(value.value) == true)
			m_then->execute();
		else
			if (m_else != nullptr)
				m_else->execute();
	}

	virtual void regulateTree() {
		m_expression->setParentBlock(m_parentBlock);
		m_expression->regulateTree();

		m_then->setParentBlock(m_parentBlock);
		m_then->regulateTree();

		if (m_else) {
			m_else->setParentBlock(m_parentBlock);
			m_else->regulateTree();
		}
	}

protected:
	ExpressionNode* m_expression;
	StatementNode* m_then;
	StatementNode* m_else;
};