#pragma once

#include <string>
#include "StatementNode.h"
#include "ExpressionNode.h"
#include "BlockNode.h"

class WriteStatementNode : public StatementNode {
public:
	WriteStatementNode(const std::vector<ExpressionNode*>& expressions)
		: m_expressions(expressions) {

	}

	~WriteStatementNode() {

	}

	virtual void execute() {
		BlockNode* block = static_cast<BlockNode*>(m_parentBlock);

		for (auto expression : m_expressions) {
			PasValue v = expression->calculate();

			if (v.type == PasValue::Type::Boolean)
				std::cout << v.get<bool>() << " ";
			else if (v.type == PasValue::Type::Integer)
				std::cout << v.get<int>() << " ";
			else if (v.type == PasValue::Type::Real)
				std::cout << v.get<double>() << " ";
			else
				throw std::exception("wrong operation");
		}

		std::cout << std::endl;
	}

	virtual void regulateTree() {
		for (auto expression : m_expressions) {
			expression->setParentBlock(m_parentBlock);
			expression->regulateTree();
		}
	}

protected:
	std::vector<ExpressionNode*> m_expressions;
};