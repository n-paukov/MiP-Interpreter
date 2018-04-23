#pragma once

#include <string>
#include "StatementNode.h"
#include "ExpressionNode.h"

class CallProcedureNode : public StatementNode {
public:
	CallProcedureNode(const std::string& procedure) 
		: m_procedure(procedure) 
	{

	}

protected:
	std::string m_procedure;
};