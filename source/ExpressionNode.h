#pragma once

#include <string>
#include "Node.h"

class ExpressionNode : public Node {
public:
	virtual PasValue calculate() {
		return PasValue();
	}

protected:

};