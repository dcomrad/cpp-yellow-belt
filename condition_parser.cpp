#include "condition_parser.h"

shared_ptr<Node> ParseCondition(istream& is) {
	vector<Token> tokens = Tokenize(is);
	vector<Token>::iterator current = tokens.begin();
	shared_ptr<Node> top_node = ParseExpression(current, tokens.end(), 0u);

  if (!top_node) {
    top_node = make_shared<EmptyNode>();
  }

  if (current != tokens.end()) {
    throw logic_error("Unexpected tokens after condition");
  }

  return top_node;
}
