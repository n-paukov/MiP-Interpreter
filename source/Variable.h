#pragma once

#include "Types.h"

struct Variable {
	Variable() : type(PasValue::Type::Null) {
		
	}

	Variable(PasValue::Type type) : type(type) {

	}

	PasValue::Type type;
	PasValue value;
};