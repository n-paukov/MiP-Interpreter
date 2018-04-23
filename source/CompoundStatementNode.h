#pragma once

#include <vector>
#include "StatementNode.h"

class CompoundStatementNode : public StatementNode {
public:
	CompoundStatementNode() {

	}

	CompoundStatementNode(const std::vector<StatementNode*>& statements)
		: m_statements(statements) {

	}

	~CompoundStatementNode() {
		for (StatementNode* statement : m_statements)
			delete statement;
	}

	virtual void execute() {
		for (auto statement : m_statements)
			statement->execute();
	}

	const std::vector<StatementNode*>& getStatements() {
		return m_statements;
	}

	virtual void regulateTree() {
		for (auto statement : m_statements) {
			statement->setParentBlock(m_parentBlock);
			statement->regulateTree();
		}
	}

protected:
	std::vector<StatementNode*> m_statements;
};