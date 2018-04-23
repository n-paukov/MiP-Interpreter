#include "SyntaxAnalyzer.h"

ProgramNode* SyntaxAnalyzer::parse(TokenStream& tokens) {
	ProgramNode* program = getProgram(tokens);
	program->regulateTree();

	return program;
}

ProgramNode* SyntaxAnalyzer::getProgram(TokenStream& tokens) {
	if (!CompareFirstToken(tokens, TokenType::Keyword, "program"))
		throw std::exception("Wrong program declaration");

	tokens.pop();

	Token id = tokens.front();

	if (id.type != TokenType::Identifier)
		throw std::exception("Program name excepted");

	std::string programName = std::get<std::string>(id.value);
	tokens.pop();

	if (!CompareFirstToken(tokens, TokenType::Punct, ';'))
		throw std::exception("Semicolon expected");

	tokens.pop();

	BlockNode* programBlockNode = getBlock(tokens);

	if (!CompareFirstToken(tokens, TokenType::Punct, '.'))
		throw std::exception("Dot expected");

	tokens.pop();

	return new ProgramNode(programName, programBlockNode);
}

BlockNode* SyntaxAnalyzer::getBlock(TokenStream& tokens) {
	auto variables = getVariablesDeclaration(tokens);
	CompoundStatementNode* statementPart = getCompoundStatementNode(tokens);

	return new BlockNode(variables, statementPart);
}

std::map<std::string, Variable> SyntaxAnalyzer::getVariablesDeclaration(TokenStream& tokens) {
	std::map<std::string, Variable> variables;

	if (!CompareFirstToken(tokens, TokenType::Keyword, "var"))
		return variables;

	tokens.pop();

	if (tokens.front().type != TokenType::Identifier)
		throw std::exception("Wrong variable declaration");

	while (tokens.front().type == TokenType::Identifier) {
		std::vector<std::string> varNames;

		while (tokens.front().type == TokenType::Identifier) {
			varNames.push_back(std::get<std::string>(tokens.front().value));
			tokens.pop();

			if (!CompareFirstToken(tokens, TokenType::Punct, ','))
				break;

			tokens.pop();
		}

		if (!CompareFirstToken(tokens, TokenType::Punct, ':'))
			throw std::exception("Colon expected");

		tokens.pop();

		if (tokens.front().type != TokenType::Identifier)
			throw std::exception("Type name expected");

		std::string typeName = std::get<std::string>(tokens.front().value);
		tokens.pop();

		if (!CompareFirstToken(tokens, TokenType::Punct, ';'))
			throw std::exception("Semicolon expected");

		tokens.pop();

		for (std::string varName : varNames) {
			PasValue::Type varType;

			if (typeName == "integer")
				varType = PasValue::Type::Integer;
			else if (typeName == "boolean")
				varType = PasValue::Type::Boolean;
			else if (typeName == "real")
				varType = PasValue::Type::Real;
			else if (typeName == "char")
				varType = PasValue::Type::Char;
			else if (typeName == "string")
				varType = PasValue::Type::String;
			else
				throw std::exception("Wrong variable type");

			variables[varName] = Variable(varType);
		}
	}

	return variables;
}

std::pair<std::string, Variable> SyntaxAnalyzer::getVariableDeclaration(TokenStream& tokens) {
	Token t = tokens.front();

	if (t.type != TokenType::Identifier)
		throw std::exception("Wrong variableDeclaration");

	std::string varName = std::get<std::string>(t.value);
}

CompoundStatementNode* SyntaxAnalyzer::getStatementPart(TokenStream& tokens) {
	return getCompoundStatementNode(tokens);
}

CompoundStatementNode* SyntaxAnalyzer::getCompoundStatementNode(TokenStream& tokens) {
	if (!CompareFirstToken(tokens, TokenType::Keyword, "begin"))
		throw std::exception("Begin expected");

	tokens.pop();

	std::vector<StatementNode*> statements;

	while (true) {
		if (!statements.empty() && !CompareFirstToken(tokens, TokenType::Punct, ';'))
			throw std::exception("Semicolon excepted");

		if (!statements.empty())
			tokens.pop();

		StatementNode* statement = getStatement(tokens);

		if (statement == nullptr)
			break;

		statements.push_back(statement);
	}

	if (statements.empty())
		throw std::exception("Statement expected");

	if (!CompareFirstToken(tokens, TokenType::Keyword, "end"))
		throw std::exception("End expected");

	tokens.pop();

	return new CompoundStatementNode(statements);
}

StatementNode* SyntaxAnalyzer::getStatement(TokenStream& tokens) {
	Token t = tokens.front();

	if (CompareFirstToken(tokens, TokenType::Keyword, "begin"))
		return getCompoundStatementNode(tokens);
	else if (CompareFirstToken(tokens, TokenType::Keyword, "if"))
		return getIfStatement(tokens);
	else if (CompareFirstToken(tokens, TokenType::Keyword, "while"))
		return getWhileStatement(tokens);
	else if (CompareFirstToken(tokens, TokenType::Keyword, "read"))
		return getReadStatement(tokens);
	else if (CompareFirstToken(tokens, TokenType::Keyword, "write"))
		return getWriteStatement(tokens);
	else if (t.type == TokenType::Identifier) {
		std::string idValue = std::get<std::string>(t.value);

		tokens.pop();

		if (CompareFirstToken(tokens, TokenType::Operation, ":=")) {
			tokens.pop();
			ExpressionNode* expression = getExpression(tokens);

			return new AssignmentNode(idValue, expression);
		}

		return new CallProcedureNode(idValue);
	}

	return nullptr;
}

ReadStatementNode* SyntaxAnalyzer::getReadStatement(TokenStream& tokens) {
	if (!CompareFirstToken(tokens, TokenType::Keyword, "read"))
		throw std::exception("Read expected");

	tokens.pop();

	if (!CompareFirstToken(tokens, TokenType::Bracket, '('))
		throw std::exception("'(' expected");

	tokens.pop();

	std::vector<std::string> variablesNames = getReadStatementArgs(tokens);

	if (!CompareFirstToken(tokens, TokenType::Bracket, ')'))
		throw std::exception("')' expected");

	tokens.pop();

	return new ReadStatementNode(variablesNames);
}

std::vector<std::string> SyntaxAnalyzer::getReadStatementArgs(TokenStream& tokens) {
	std::vector<std::string> args;

	while (!CompareFirstToken(tokens, TokenType::Bracket, ')')) {
		if (tokens.front().type != TokenType::Identifier)
			throw std::exception("Identifier expected");

		args.push_back(std::get<std::string>(tokens.pop().value));

		if (!CompareFirstToken(tokens, TokenType::Punct, ','))
			break;
		else
			tokens.pop();
	}

	return args;
}

WriteStatementNode* SyntaxAnalyzer::getWriteStatement(TokenStream& tokens) {
	if (!CompareFirstToken(tokens, TokenType::Keyword, "write"))
		throw std::exception("Write expected");

	tokens.pop();

	if (!CompareFirstToken(tokens, TokenType::Bracket, '('))
		throw std::exception("'(' expected");

	tokens.pop();

	std::vector<ExpressionNode*> expressions = getWriteStatementArgs(tokens);

	if (!CompareFirstToken(tokens, TokenType::Bracket, ')'))
		throw std::exception("')' expected");

	tokens.pop();

	return new WriteStatementNode(expressions);
}

std::vector<ExpressionNode*> SyntaxAnalyzer::getWriteStatementArgs(TokenStream& tokens) {
	std::vector<ExpressionNode*> args;

	while (!CompareFirstToken(tokens, TokenType::Bracket, ')')) {
		args.push_back(getExpression(tokens));

		if (!CompareFirstToken(tokens, TokenType::Punct, ','))
			break;
		else
			tokens.pop();
	}

	return args;
}

IfStatementNode* SyntaxAnalyzer::getIfStatement(TokenStream& tokens) {
	if (!CompareFirstToken(tokens, TokenType::Keyword, "if"))
		throw std::exception("if expected");

	tokens.pop();

	ExpressionNode* expression = getExpression(tokens);

	if (!CompareFirstToken(tokens, TokenType::Keyword, "then"))
		throw std::exception("then expected");

	tokens.pop();

	StatementNode* thenStatement = getStatement(tokens);

	if (thenStatement == nullptr)
		throw std::exception("Then statement expected");

	StatementNode* elseStatement = nullptr;

	if (CompareFirstToken(tokens, TokenType::Keyword, "else")) {
		tokens.pop();

		elseStatement = getStatement(tokens);

		if (elseStatement == nullptr)
			throw std::exception("Else statement expected");

	}

	return new IfStatementNode(expression, thenStatement, elseStatement);
}

WhileStatementNode* SyntaxAnalyzer::getWhileStatement(TokenStream& tokens) {
	if (!CompareFirstToken(tokens, TokenType::Keyword, "while"))
		throw std::exception("while expected");

	tokens.pop();

	ExpressionNode* expression = getExpression(tokens);

	if (!CompareFirstToken(tokens, TokenType::Keyword, "do"))
		throw std::exception("do expected");

	tokens.pop();

	StatementNode* doStatement = getStatement(tokens);

	if (doStatement == nullptr)
		throw std::exception("Do statement expected");

	return new WhileStatementNode(expression, doStatement);
}

ExpressionNode* SyntaxAnalyzer::getExpression(TokenStream& tokens) {
	ExpressionNode* leftExpression = getSimpleExpression(tokens);

	if (tokens.front().type == TokenType::Operation) {
		std::string operation = std::get<std::string>(tokens.front().value);

		if (operation != "=" && operation != "<>" && operation != "<" &&
			operation != "<=" && operation != ">=" && operation != ">")
		{
			throw std::exception("Relational operator expected");
		}

		tokens.pop();

		ExpressionNode* rightExpression = getSimpleExpression(tokens);

		return new BinaryOperationNode(leftExpression, operation, rightExpression);
	}

	return leftExpression;
}

ExpressionNode* SyntaxAnalyzer::getSimpleExpression(TokenStream& tokens) {
	ExpressionNode* left = getTerm(tokens);

	if (tokens.front().type == TokenType::Operation) {
		std::string operation = std::get<std::string>(tokens.front().value);

		if (operation == "+" || operation == "-" || operation == "or") {
			tokens.pop();

			return new BinaryOperationNode(left, operation, getSimpleExpression(tokens));
		}
	}

	return left;
}

ExpressionNode* SyntaxAnalyzer::getTerm(TokenStream& tokens) {
	ExpressionNode* left = getFactor(tokens);

	if (tokens.front().type == TokenType::Operation) {
		std::string operation = std::get<std::string>(tokens.front().value);

		if (operation == "*" || operation == "/" || operation == "div" || operation == "and") {
			tokens.pop();

			return new BinaryOperationNode(left, operation, getTerm(tokens));
		}
	}

	return left;
}

ExpressionNode* SyntaxAnalyzer::getFactor(TokenStream& tokens) {
	if (CompareFirstToken(tokens, TokenType::Operation, "+") || CompareFirstToken(tokens, TokenType::Operation, "-")) {
		std::string sign = std::get<std::string>(tokens.front().value);
		tokens.pop();

		return new UnaryOperationNode(getFactor(tokens), sign);
	}
	else if (tokens.front().type == TokenType::Identifier) {
		std::string idValue = std::get<std::string>(tokens.pop().value);

		if (idValue == "true" || idValue == "false") {
			return new ConstantNode(PasValue(idValue == "true"));
		}

		return new VariableValueNode(idValue);
	}
	else if (CompareFirstToken(tokens, TokenType::Keyword, "not")) {
		tokens.pop();

		return new UnaryOperationNode(getFactor(tokens), "not");
	}
	else if (CompareFirstToken(tokens, TokenType::Bracket, '(')) {
		tokens.pop();

		ExpressionNode* expr = getExpression(tokens);

		if (!CompareFirstToken(tokens, TokenType::Bracket, ')')) {
			throw std::exception("')' expected");
		}

		tokens.pop();

		return expr;
	}
	else {
		ExpressionNode* expr = nullptr;

		if (tokens.front().type == TokenType::IntNumber) {
			PasValue v(std::get<int>(tokens.front().value));
			expr = new ConstantNode(v);
		}
		else if (tokens.front().type == TokenType::RealNumber) {
			PasValue v(std::get<double>(tokens.front().value));
			expr = new ConstantNode(v);
		}
		else if (tokens.front().type == TokenType::Char) {
			PasValue v(std::get<char>(tokens.front().value));
			expr = new ConstantNode(v);
		}
		else if (tokens.front().type == TokenType::String) {
			PasValue v(std::get<char>(tokens.front().value));
			expr = new ConstantNode(v);
		}
		else
			throw std::exception("factor excepted");

		tokens.pop();

		return expr;
	}
}

bool SyntaxAnalyzer::CompareFirstToken(TokenStream& tokens, TokenType type, std::string value) {
	Token t = tokens.front();

	if (t.type != type || std::get<std::string>(t.value) != value)
		return false;

	return true;
}

bool SyntaxAnalyzer::CompareFirstToken(TokenStream& tokens, TokenType type, char value) {
	Token t = tokens.front();

	if (t.type != type || std::get<char>(t.value) != value)
		return false;

	return true;
}
