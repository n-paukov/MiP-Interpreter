#pragma once

#include <map>
#include "Tokenizer.h"
#include "Variable.h"
#include "ProgramNode.h"
#include "IfStatementNode.h"
#include "WhileStatementNode.h"
#include "AssignmentNode.h"
#include "CallProcedureNode.h"
#include "BinaryOperationNode.h"
#include "UnaryOperationNode.h"
#include "ConstantNode.h"
#include "VariableValueNode.h"
#include "ReadStatementNode.h"
#include "WriteStatementNode.h"
#include <optional>

class SyntaxAnalyzer {
public:
	ProgramNode* parse(TokenStream& tokens);

public:
	ProgramNode* getProgram(TokenStream& tokens);
	BlockNode* getBlock(TokenStream& tokens);
	std::map<std::string, Variable> getVariablesDeclaration(TokenStream& tokens);
	CompoundStatementNode* getStatementPart(TokenStream& tokens);
	std::pair<std::string, Variable> getVariableDeclaration(TokenStream& tokens);

	CompoundStatementNode* getCompoundStatementNode(TokenStream& tokens);
	StatementNode* getStatement(TokenStream& tokens);
	IfStatementNode* getIfStatement(TokenStream& tokens);
	WhileStatementNode* getWhileStatement(TokenStream& tokens);

	ExpressionNode* getExpression(TokenStream& tokens);
	ExpressionNode* getSimpleExpression(TokenStream& tokens);
	ExpressionNode* getTerm(TokenStream& tokens);
	ExpressionNode* getFactor(TokenStream& tokens);

	ReadStatementNode* getReadStatement(TokenStream& tokens);
	std::vector<std::string> getReadStatementArgs(TokenStream& tokens);

	WriteStatementNode* getWriteStatement(TokenStream& tokens);
	std::vector<ExpressionNode*> getWriteStatementArgs(TokenStream& tokens);

private:
	bool CompareFirstToken(TokenStream& tokens, TokenType type, std::string value);
	bool CompareFirstToken(TokenStream& tokens, TokenType type, char value);

};