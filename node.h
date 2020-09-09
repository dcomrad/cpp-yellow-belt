#pragma once

#include "date.h"

#include <string>
#include <memory>

using namespace std;

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

enum class LogicalOperation {
	Or,
	And
};

template <typename T>
bool CompareFileds (const Comparison cmp, const T& lhs, const T& rhs) {
	switch (cmp) {
		case Comparison::Equal:
			return lhs == rhs;
		case Comparison::NotEqual:
			return lhs != rhs;
		case Comparison::Greater:
			return lhs > rhs;
		case Comparison::GreaterOrEqual:
			return lhs >= rhs;
		case Comparison::Less:
			return lhs < rhs;
		case Comparison::LessOrEqual:
			return lhs <= rhs;
		default:
			return false;
	}
}

class Node {
public:
	virtual ~Node() = default;
	virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node {
public:
	bool Evaluate(const Date& date, const string& event) const override;
};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(const Comparison _cmp, const Date& _date);
	bool Evaluate(const Date& _date, const string& _event) const override;
private:
	const Comparison cmp;
	const Date date;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(const Comparison _cmp, const string& _event);
	bool Evaluate(const Date& _date, const string& _event) const override;
private:
	const Comparison cmp;
	const string event;
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(const LogicalOperation _op, const shared_ptr<Node> _left, const shared_ptr<Node> _right);
	bool Evaluate(const Date& _date, const string& _event) const override;
private:
	const LogicalOperation op;
	const shared_ptr<Node> left;
	const shared_ptr<Node> right;
};
