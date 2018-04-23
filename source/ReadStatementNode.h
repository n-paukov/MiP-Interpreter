#pragma once

#include <string>
#include "StatementNode.h"
#include "ExpressionNode.h"
#include "BlockNode.h"

class ReadStatementNode : public StatementNode {
public:
	ReadStatementNode(const std::vector<std::string>& variables)
		: m_variables(variables) {

	}

	~ReadStatementNode() {
		
	}

	virtual void execute() {
		BlockNode* block = static_cast<BlockNode*>(m_parentBlock);

		for (const std::string& varName : m_variables) {
			auto& var = block->m_variables[varName];

			if (var.type == PasValue::Type::Boolean) {
				bool v;
				std::cin >> v;

				var.value = PasValue(v);
			}
			else if (var.type == PasValue::Type::Integer) {
				int v;
				std::cin >> v;

				var.value = PasValue(v);
			}
			else if (var.type == PasValue::Type::Real) {
				double v;
				std::cin >> v;

				var.value = PasValue(v);
			}
			else
				throw std::exception("wrong operation");
		}
	}

protected:
	std::vector<std::string> m_variables;
};