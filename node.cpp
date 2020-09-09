#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const string& event) const {
	return true;
}

DateComparisonNode::DateComparisonNode(const Comparison _cmp, const Date& _date) : cmp(_cmp), date(_date) {}

bool DateComparisonNode::Evaluate(const Date& _date, const string& _event) const {
	return CompareFileds(cmp, _date, date);
}

EventComparisonNode::EventComparisonNode(const Comparison _cmp, const string& _event): cmp(_cmp), event(_event) {}

bool EventComparisonNode::Evaluate(const Date& _date, const string& _event) const {
	return CompareFileds(cmp, _event, event);
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation _op, const shared_ptr<Node> _left, const shared_ptr<Node> _right) : op(_op), left(_left), right(_right) {}

bool LogicalOperationNode::Evaluate(const Date& _date, const string& _event) const {
	switch (op) {
		case LogicalOperation::And:
			return left->Evaluate(_date, _event) && right->Evaluate(_date, _event);
		case LogicalOperation::Or:
			return left->Evaluate(_date, _event) || right->Evaluate(_date, _event);
		default:
			return false;
	}
}


