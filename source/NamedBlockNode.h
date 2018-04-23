#pragma once

#include <string>
#include "BlockNode.h"

class NamedBlockNode : public BlockNode {
public:
	NamedBlockNode(const std::string& name, BlockNode* blockNode) {
		m_name = name;
		this->m_statementPart = blockNode->getStatementsPart();
		this->m_variables = blockNode->getVariables();
	}

	virtual void regulateTree() {
		m_statementPart->setParentBlock(m_parentBlock);
		m_statementPart->regulateTree();
	}

protected:
	std::string m_name;
};