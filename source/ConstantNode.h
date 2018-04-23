#pragma once

#include <string>
#include "ExpressionNode.h"
#include "Types.h"

class ConstantNode : public ExpressionNode {
public:
	ConstantNode(PasValue value)
		: m_value(value) {

	}

	virtual PasValue calculate() {
		return m_value;
	}

protected:
	PasValue m_value;
};