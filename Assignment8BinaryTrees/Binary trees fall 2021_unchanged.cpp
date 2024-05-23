// Copyright 2021, Bradley Peterson, Weber State University, all rights reserved. (11/2021)

#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <cmath>
#include <cstdio>

using std::stack;
using std::istringstream;
using std::ostringstream;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::pow;

void TreeParser::initialize() {
	expression = "";
	position = 0;
	while (!mathStack.empty()) {
		mathStack.pop();
	}
}

double TreeParser::castStrToDouble(const string &s) {
	istringstream iss(s);
	double x;
	iss >> x;
	return x;
} 

string TreeParser::castDoubleToStr(const double d) {
	ostringstream oss;
	oss << d;
	return oss.str();

} 

TreeParser::TreeParser() {
	initialize();
}


void TreeParser::displayParseTree() {
	cout << "The expression seen using in-order traversal: "; 
	inOrderTraversal();
	cout << endl;
	cout << "The expression seen using post-order traversal: "; 
	postOrderTraversal();
	cout << endl;
	
}

void pressEnterToContinue() {
	printf("Press Enterto continue\n");

	cin.get();

}

// Copyright 2021, Bradley Peterson, Weber State University, all rights reserved. (07/2021)

int main() {

	TreeParser *tp = new TreeParser;
	
	string expression = "(4+7)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 11 as a double output
	
	expression = "(7-4)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 3 as a double output

  expression = "(9*5)";
  tp->processExpression(expression);
  tp->displayParseTree();
  cout << "The result is: " << tp->computeAnswer() << endl; //Should display 45 as a double output

	expression = "(4^3)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 64 as a double output

	expression = "((2-5)-5)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display -8 as a double output
	
	expression = "(5 * (6/2))";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 15 as a double output
	
	expression = "((6 / 3) + (8 * 2))";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 18 as a double output

	expression = "(543+321)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 864 as a double output

	expression = "(7.5-3.25)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 4.25 as a double output

	expression = "(5 + (34 - (7 * (32 / (16 * 0.5)))))";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 11 as a double output

  expression = "((5*(3+2))+(7*(4+6)))";
  tp->processExpression(expression);
  tp->displayParseTree();
  cout << "The result is: " << tp->computeAnswer() << endl; //Should display 95 as a double output


	expression = "(((2+3)*4)+(7+(8/2)))";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display 31 as a double output

	expression = "(((((3+12)-7)*120)/(2+3))^3)";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display close to 7077888 as a double output 
                                                            //NOTE, it won't be exact, it will display as scientific notation!
	
	expression = "(((((9+(2*(110-(30/2))))*8)+1000)/2)+(((3^4)+1)/2))";
	tp->processExpression(expression);
	tp->displayParseTree();
	cout << "The result is: " << tp->computeAnswer() << endl; //Should display close to 1337 as a double/decimal output
	
	pressEnterToContinue();
	return 0;
}
