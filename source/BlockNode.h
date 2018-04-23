#pragma once

#include <map>
#include "Variable.h"
#include "CompoundStatementNode.h"
#include "Node.h"

class BlockNode : public Node {
	friend class StatementNode;
	friend class AssignmentNode;
	friend class VariableValueNode;
	friend class ReadStatementNode;
	friend class WriteStatementNode;

public:
	BlockNode() {

	}

	BlockNode(const std::map<std::string, Variable>& variables, CompoundStatementNode* statementPart) 
		: m_variables(variables), m_statementPart(statementPart) {

	}
	
	~BlockNode() {
		delete m_statementPart;
	}

	std::map<std::string, Variable> getVariables() const { return m_variables; }
	CompoundStatementNode* getStatementsPart() const { return m_statementPart; }
	
	virtual void regulateTree() {
		m_statementPart->setParentBlock(m_parentBlock);
		m_statementPart->regulateTree();
	}
protected:
	std::map<std::string, Variable> m_variables;
	CompoundStatementNode* m_statementPart;
};