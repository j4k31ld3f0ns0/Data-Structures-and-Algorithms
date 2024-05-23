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
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::pow;

struct Node {
	string data{""};
	Node* left;
	Node* right;
};

class TreeParser {
	/*
	Notes on binary trees
		L = left, R = right, N = node (referring to root node)
		tree traversal methods
			in-order traversal (LNR)
			pre-order traversal (NLR)
			post-order traversal (LRN)
	*/
private:
	stack<string> mathStack;
	double castStrToDouble(string const& s); //given
	string castDoubleToStr(const double d); //given
	void initialize(); //given

	void inOrderTraversal(Node* p);
	void postOrderTraversal(Node* p);

	bool isDigit(char c);
	bool isOperator(char c);
	void processExpression(Node* p); //raw pointer implementation with Node* p
	void computeAnswer(Node* p);
protected:
	string expression; //the string original mathematical expression to work on
	int position; //position in given expression, char position in string
	Node* root;
public:
	TreeParser();
	void displayParseTree(); //display binary tree of expression in both in-order and post-order notation.
	void processExpression(string& expression); //get things started and call private method under same name. Create a node and have root point to it, pass into private expression for processing.
	string computeAnswer();
	void inOrderTraversal();
	void postOrderTraversal();
};

void TreeParser::initialize() {
	expression = "";
	position = 0;
	while (!mathStack.empty()) {
		mathStack.pop();
	}
}

void TreeParser::inOrderTraversal()
{
	//LAR - left, ACT, right
	inOrderTraversal(root);
}
void TreeParser::inOrderTraversal(Node* p) {
	if (p) {
		inOrderTraversal(p->left);
		cout << p->data << " ";
		inOrderTraversal(p->right);
	}
}

void TreeParser::postOrderTraversal()
{
	//Left, Right, ACT
	postOrderTraversal(root);
}
void TreeParser::postOrderTraversal(Node* p) {
	if (p) {
		inOrderTraversal(p->left);
		inOrderTraversal(p->right);
		cout << p->data << " ";
	}
}

bool TreeParser::isDigit(char c)
{
	if (c < 58 && c > 47) {
		return true;
	}
	else {
		return false;
	}
}

bool TreeParser::isOperator(char c)
{
	// Math operators are +, -, *, /, ^
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
		return true;
	}
	else {
		return false;
	}
}

double TreeParser::castStrToDouble(const string& s) {
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

void TreeParser::processExpression(string& expression) //gets the processing started
{
	if (!expression.empty()) {
		//not empty, store expression
		this->expression = expression;
		this->position = 0;
		this->root = new Node();
		processExpression(root);
	}
}

void TreeParser::processExpression(Node* p)
{
	while (this->position < (this->expression.size() - 1)) {
		if (expression[position] == '(') { //if (
			Node* newNode = new Node();
			//newNode->data += expression[position]; //insert '(' char to data
			position++;
			p->left = newNode;
			processExpression(newNode); //"recursively go left"?
		}
		else if (expression[position] == '.' || isDigit(expression[position])) { //if digit or decimal
			string tempDigit{""};
			do {
				tempDigit += expression[position];
				position++;
			} while (isDigit(expression[position]) || expression[position] == '.');
			p->data = tempDigit;
			return;
		}
		else if (isOperator(expression[position])) { //if operator
			Node* newNode = new Node();
			p->right = newNode;
			p->data = expression[position];
			position++;
			processExpression(newNode);
		}
		else if (expression[position] == ')') { //if )
			position++;
			return;
		}
		else if (expression[position] == ' ') {
			position++;
		}
	}
}

string TreeParser::computeAnswer()
{
	computeAnswer(root);
	return mathStack.top();
}

void TreeParser::computeAnswer(Node* p)
{
	//uses postfix traversal - left, right, act on node
	if (p) {
		computeAnswer(p->left);//go left
		computeAnswer(p->right);//go right
								//act below here

		if (isDigit(p->data[0])) { //since it was previously split into operands and operators, if the first char is a digit, assuming split was correct
			mathStack.push(p->data);
		}
		else if (isOperator(p->data[0])) { //works with operators too since operators are at most 1 character
			//pull two numbers off stack, then compute them and stick them back on stack
			// Math operators are +, -, *, /, ^
			double calculatedAnswer = 0;

			auto leftOperand = castStrToDouble(mathStack.top());
			mathStack.pop();
			auto rightOperand = castStrToDouble(mathStack.top());
			mathStack.pop();

			switch (p->data[0]) {
			case '+':
				calculatedAnswer = rightOperand + leftOperand;
				break;
			case '-':
				calculatedAnswer = rightOperand - leftOperand;
				break;
			case '*':
				calculatedAnswer = rightOperand * leftOperand;
				break;
			case '/':
				calculatedAnswer = rightOperand / leftOperand;
				break;
			case '^':
				calculatedAnswer = pow(rightOperand, leftOperand);
				break;
			}
			mathStack.push(castDoubleToStr(calculatedAnswer));
		}
	}
}

void pressEnterToContinue() {
	printf("Press Enter to continue\n");

	cin.get();

}

// Copyright 2021, Bradley Peterson, Weber State University, all rights reserved. (07/2021)

int main() {

	TreeParser* tp = new TreeParser;

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
