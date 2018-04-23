#pragma once

#include <string>
#include "ExpressionNode.h"
#include "BlockNode.h"

class VariableValueNode : public ExpressionNode {
public:
	VariableValueNode(const std::string& name)
		: m_name(name) {

	}

	virtual PasValue calculate() {
		return static_cast<BlockNode*>(m_parentBlock)->m_variables[m_name].value;
	}

protected:
	std::string m_name;
};