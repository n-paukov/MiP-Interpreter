#pragma once

#include "NamedBlockNode.h"

class ProgramNode : public NamedBlockNode {
public:
	ProgramNode(const std::string& name, BlockNode* blockNode) 
		: NamedBlockNode(name, blockNode) {

	}

	virtual void print(int level = 0) {
		std::cout << "program(" << this->m_name << "):" << std::endl;
		std::cout << "-variables: ";

		for (auto var : m_variables)
			std::cout << var.first << "[" << typeid(var.second.type).name() << "]  ";

		std::cout << std::endl;

		m_statementPart->print(level+1);
	
	}

	virtual void execute() {
		m_statementPart->execute();
	}

	virtual void regulateTree() {
		m_statementPart->setParentBlock(this);
		m_statementPart->regulateTree();
	}
};