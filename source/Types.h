#pragma once


struct PasValue {
	enum class Type {
		Boolean, Integer, Real, Char, String, Null
	};
	
	using Value = std::variant<bool, int, double, char, std::string>;

	PasValue() : type(Type::Null) {
		
	}

	PasValue(bool value) : type(Type::Boolean), value(value) {

	}

	PasValue(int value) : type(Type::Integer), value(value) {

	}

	PasValue(double value) : type(Type::Real), value(value) {

	}

	PasValue(char value) : type(Type::Char), value(value) {

	}

	PasValue(const std::string& value) : type(Type::String), value(value) {

	}

	template<typename T>
	T get() {
		return std::get<T>(value);
	}

	friend const PasValue& operator+(const PasValue& v) {
		if (v.type != Type::Integer && v.type != Type::Real)
			throw std::exception("Wrong operation");

		return PasValue(v);
	}

	friend const PasValue operator-(const PasValue& v) {
		if (v.type != Type::Integer && v.type != Type::Real)
			throw std::exception("Wrong operation");

		if (v.type == Type::Integer)
			return -std::get<int>(v.value);
		else
			return -std::get<double>(v.value);
	}

	friend const PasValue operator+(const PasValue& left, const PasValue& right) {
		PasValue result;

		if (left.type == Type::Integer && right.type == Type::Integer) {
			return PasValue(std::get<int>(left.value) + std::get<int>(right.value));
		}
		else if (left.type == Type::Real && right.type == Type::Integer) {
			return PasValue(std::get<double>(left.value) + std::get<int>(right.value));
		}
		else if (left.type == Type::Integer && right.type == Type::Real) {
			return PasValue(std::get<int>(left.value) + std::get<double>(right.value));
		}
		else if (left.type == Type::Real && right.type == Type::Real) {
			return PasValue(std::get<double>(left.value) + std::get<double>(right.value));
		}
		else
			throw std::exception("Wrong operation");
	}

	friend const PasValue operator-(const PasValue& left, const PasValue& right) {
		return left + (-right);
	}

	friend const PasValue operator*(const PasValue& left, const PasValue& right) {
		PasValue result;

		if (left.type == Type::Integer && right.type == Type::Integer) {
			return PasValue(std::get<int>(left.value) * std::get<int>(right.value));
		}
		else if (left.type == Type::Real && right.type == Type::Integer) {
			return PasValue(std::get<double>(left.value) * std::get<int>(right.value));
		}
		else if (left.type == Type::Integer && right.type == Type::Real) {
			return PasValue(std::get<int>(left.value) * std::get<double>(right.value));
		}
		else if (left.type == Type::Real && right.type == Type::Real) {
			return PasValue(std::get<double>(left.value) * std::get<double>(right.value));
		}
		else
			throw std::exception("Wrong operation");
	}

	friend const PasValue operator&&(const PasValue& left, const PasValue& right) {
		if (left.type != PasValue::Type::Boolean || right.type != PasValue::Type::Boolean)
			throw std::exception("Wrong operation");

		return PasValue(std::get<bool>(left.value) && std::get<bool>(right.value));
	}

	friend const PasValue operator||(const PasValue& left, const PasValue& right) {
		if (left.type != PasValue::Type::Boolean || right.type != PasValue::Type::Boolean)
			throw std::exception("Wrong operation");
			
		return PasValue(std::get<bool>(left.value) || std::get<bool>(right.value));
	}

	friend const PasValue operator!(const PasValue& v) {
		if (v.type != PasValue::Type::Boolean)
			throw std::exception("Wrong operation");

		return PasValue(!std::get<bool>(v.value));
	}

	friend const PasValue operator==(const PasValue& left, const PasValue& right) {
		if (left.type != right.type)
			throw std::exception("Wrong operation");

		if (left.type == PasValue::Type::Integer)
			return PasValue(std::get<int>(left.value) == std::get<int>(right.value));
		else if (left.type == PasValue::Type::Real)
			return PasValue(std::get<double>(left.value) == std::get<double>(right.value));
		else if (left.type == PasValue::Type::Boolean)
			return PasValue(std::get<bool>(left.value) == std::get<bool>(right.value));

		throw std::exception("Wrong operation");
	}

	friend const PasValue operator!=(const PasValue& left, const PasValue& right) {
		return !(left == right);
	}

	friend const PasValue operator>(const PasValue& left, const PasValue& right) {
		if (left.type != right.type)
			throw std::exception("Wrong operation");

		if (left.type == PasValue::Type::Integer)
			return PasValue(std::get<int>(left.value) > std::get<int>(right.value));
		else if (left.type == PasValue::Type::Real)
			return PasValue(std::get<double>(left.value) > std::get<double>(right.value));

		throw std::exception("Wrong operation");
	}

	friend const PasValue operator>=(const PasValue& left, const PasValue& right) {
		return left == right && left > right;
	}

	friend const PasValue operator<(const PasValue& left, const PasValue& right) {
		return !(left >= right);
	}

	friend const PasValue operator<=(const PasValue& left, const PasValue& right) {
		return !(left > right);
	}

	Type type;
	Value value;
};