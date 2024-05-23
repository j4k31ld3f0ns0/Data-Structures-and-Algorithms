//Copyright 2021, Bradley Peterson, Weber State University, All rights reserved. (Oct 2021)

#include <iostream>
#include <map>
#include <algorithm>
#include <list>
#include <sstream>
#include <memory>
#include <string>
#include <vector>

template <typename T> class DoublyLinkedList; //prototypes
template <typename T> class Iterator;

using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::string;
using std::stringstream;
using std::iter_swap;
using std::make_shared;
using std::shared_ptr;
using std::vector;


//******************
//The Node class
//******************
template <typename T>
struct Node {
	T data{};
	shared_ptr<Node<T>> prev;
	shared_ptr<Node<T>> next;
};

//******************
//The Iterator class
//******************
template <typename T>
class Iterator {
	friend class DoublyLinkedList<T>;
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = T;
	using difference_type = int;
	using pointer = T*;
	using reference = T&;

	// TODO: Implement the following:
	//operator*
	//operator++ prefix  ends with return *this;
	//operator++ postfix  starts with auto temp = *this;  advances the "this"...;   return temp;
	//operator-- prefix
	//operator!=
	//operator==
	T& operator*();
	Iterator<T> operator++();
	Iterator<T> operator++(int);
	Iterator<T> operator--();
	bool operator!=(const Iterator& rhs);
	bool operator==(const Iterator& rhs);

private:

	// TODO: supply two data members
	//You need a shared pointer to a node
	shared_ptr<Node<T>> currentNode {nullptr};
	//You need a boolean pastTheEnd, initialized to false.
	bool pastTheEnd{ false };
};

//***********************************
//The Iterator class methods
//***********************************

// TODO: code the definitions for all the iterator methods.
template<typename T>
T& Iterator<T>::operator*()
{
	if (!pastTheEnd) { //if its not past the last item, access info
		return currentNode->data;
	}
	else {
		cout << "current node is past the end, no data to retrieve." << endl;
	}
}

template<typename T>
Iterator<T> Iterator<T>::operator++() //prefix
{
	if (!pastTheEnd) {
		if (currentNode->next) { //make sure next item is valid
			currentNode = currentNode->next;
			return *this;
		}
		else { //null value next, reached the end :(
			pastTheEnd = true;
			cout << "cannot iterate further, currentNode has reached the end. pastTheEnd tripped.";
			return *this;
		}
	}
	else {
		cout << "cannot iterate further, currentNode is pastTheEnd." << endl;
		return *this;
	}
}

template<typename T>
Iterator<T> Iterator<T>::operator++(int) //postfix
{
	auto copyOfItself = *this;
	if (!pastTheEnd) {
		if (currentNode->next) { //make sure next item is valid
			//copyOfItself.currentNode = copyOfItself.currentNode->next;
			currentNode = currentNode->next;
			return copyOfItself;
		}
		else { //null value next, reached the end :(
			pastTheEnd = true;
			cout << "cannot iterate further, currentNode has reached the end. pastTheEnd tripped.";
			return *this;
		}
	}
	else {
		cout << "cannot iterate further, currentNode is pastTheEnd." << endl;
		return *this;
	}
}

template<typename T>
Iterator<T> Iterator<T>::operator--() //postfix
{
	if (currentNode->prev) { //if prev is valid
		currentNode = currentNode->prev;
		return *this;
	}
	else {
		cout << "current nodes previous node is null, cannot decrement." << endl;
	}
}

template<typename T>
bool Iterator<T>::operator!=(const Iterator& rhs)
{
	return (currentNode->data != rhs.currentNode->data);
}

template<typename T>
bool Iterator<T>::operator==(const Iterator& rhs)
{
	return (currentNode->data == rhs.currentNode->data);
}


//****************************
//The DoublyLinkedList class
//****************************
template <typename T>
class DoublyLinkedList {

public:

	//public members of the DoublyLinkedList class
	DoublyLinkedList();
	~DoublyLinkedList();
	string getStringFromList();

	void pushFront(const T&);
	void pushBack(const T&);
	// TODO: Implement a begin() and end() method.  They each return an Iterator<T> object
	Iterator<T> begin();
	Iterator<T> end();

protected:
	shared_ptr<Node<T>> first{ nullptr };
	shared_ptr<Node<T>> last{ nullptr };
	unsigned int count;
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
	count = 0;
	first = nullptr;
	last = nullptr;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	while (first != last) {
		first = first->next;
		first->prev.reset();
	}
}

template <typename T>
void DoublyLinkedList<T>::pushFront(const T& item) {
	shared_ptr<Node<T>> temp = make_shared<Node<T>>();

	temp->data = item;
	if (!first) {
		// Scenario: List is empty
		last = temp;
	}
	else {
		first->prev = temp;
		temp->next = first;
	}
	first = temp;
}

template <typename T>
void DoublyLinkedList<T>::pushBack(const T& item) {
	shared_ptr<Node<T>> temp = make_shared<Node<T>>();

	temp->data = item;
	if (!first) {
		// Scenario: List is empty
		first = temp;
	}
	else {
		last->next = temp;
		temp->prev = last;
	}
	last = temp;
}

template<typename T>
Iterator<T> DoublyLinkedList<T>::begin()
{
	Iterator<T>* iter = new Iterator<T>();
	iter->currentNode = this->first;
	return *iter;
}

template<typename T>
Iterator<T> DoublyLinkedList<T>::end()
{
	Iterator<T>* iter = new Iterator<T>();
	iter->currentNode = this->last;
	return *iter;
}

//This method helps return a string representation of all nodes in the linked list
template <typename T>
string DoublyLinkedList<T>::getStringFromList() {
	stringstream ss;
	if (!first) {
		ss << "The list is empty.";
	}
	else {

		shared_ptr<Node<T>> currentNode{ first };
		ss << currentNode->data;
		currentNode = currentNode->forward;

		while (currentNode != nullptr) {
			ss << " " << currentNode->data;
			currentNode = currentNode->forward;
		}
	}
	return ss.str();
}

//***********************************
//The DoublyLinkedList class methods
//***********************************
// TODO: implement the  the definitions for the begin() and end() methods.  They each return an Iterator<T> object



//***********************************
// TODO: complete the assignmentReverse function.
// Note that begin and end here are are iterators (The T is just saying it can be any kind of iterator).
// Your tools are ***ONLY**: ++, --, !=, ==, *,
// For example, these three lines do a swap:
//auto temp = *end;
//*end = *begin;
//*begin = temp;
//Also, this comes in handy : iter_swap(begin, end);  //Swaps the values pointed at by two iterators. 

template <typename T>
void assignmentReverse(T begin, T end) {
	--end;  // Get the container off its past-the-end state so its "pointing" at the last value in the container.
	while(begin != end) {
		T temp1 = begin;
		T temp2 = end;
		end = begin;
		begin = end;
		--end;
		begin++;
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------
//Copyright 2021, Bradley Peterson, Weber State University, All rights reserved. (Oct 2021)
//This helps with testing, do not modify.
bool checkTest(string testName, const string whatItShouldBe, const string whatItIs) {

	if (whatItShouldBe == whatItIs) {
		cout << "Passed " << testName << endl;
		return true;
	}
	else {
		cout << "****** Failed test " << testName << " ****** " << endl << "     Output was " << whatItIs << endl << "     Output should have been " << whatItShouldBe << endl;
		return false;
		exit(1);
	}
}

template <typename T>
bool checkTest(string testName, const T whatItShouldBe, const T whatItIs) {

	if (whatItShouldBe == whatItIs) {
		cout << "Passed " << testName << endl;
		return true;
	}
	else {
		cout << "****** Failed test " << testName << " ****** " << endl << "     Output was " << whatItIs << endl << "     Output should have been " << whatItShouldBe << endl;
		return false;
		exit(1);
	}
}


//This helps with testing, do not modify.
bool checkTestMemory(string testName, int whatItShouldBe, int whatItIs) {

	if (whatItShouldBe == whatItIs) {
		cout << "Passed " << testName << endl;
		return true;
	}
	else {
		cout << "***Failed test " << testName << " *** " << endl << "  There are " << whatItIs << " bytes of memory yet to be reclaimed!" << endl;
		return false;
		exit(1);
	}
}


//This helps with testing, do not modify.
void testIteratorFundamentals() {
	//cout << "|||### You need to comment in testIteratorIncrement() when it's ready and remove this ###|||" << endl;
	//cout << "|||### I strongly advise commenting in tests one at a time and testing those.  It's harder to try and do all tests at once.###|||" << endl;

	DoublyLinkedList<int> d;

	//Our test data should have all even numbers from 2 to 20
	for (int i = 2; i <= 20; i += 2) {
	  d.pushBack(i);
	}

	////Get an iterator which points at the beginning of the list
	Iterator<int> iter = d.begin();

	////Test the operator* operator
	checkTest("testIteratorFundamentals #1", 2, *iter);

	////Test the ++ prefix increment opreator
	++iter;
	checkTest("testIteratorFundamentals #2", 4, *iter);

	////Test the != operator
	////reset them back to the start
	iter = d.begin();
	Iterator<int> anotherIter = d.begin();
	if (iter != anotherIter) {
	  cout << "****** Failed testIteratorFundamentals #3 ****** " << endl << "     The two iteraters held the same data." << endl;
	}
	else {
	  cout << "Passed testIteratorFundamentals #3" << endl;
	}

	//Again test the != operator
	++iter;
	if (iter != anotherIter) {
	  cout << "Passed testIteratorFundamentals #4" << endl;
	}
	else {
	  cout << "****** Failed testIteratorFundamentals #4 ****** " << endl << "     The two iteraters held different data." << endl;
	}

	//Test the ++postfix increment
	iter = d.begin(); //reset it back to the start
	anotherIter = iter++;  //anotherIter should be at the data 2

	checkTest("testIteratorFundamentals #5", 4, *iter);
	checkTest("testIteratorFundamentals #6", 2, *anotherIter);

	// TODO:
	// We have !=, *, ++, and .begin() tested by this point.  Now test .end().  Do that with a for loop.  
	stringstream ss;
	cout << "testIteratorFundamentals test #7, this should display 2 4 6 8 10 12 14 16 18 20." << endl;
	for (auto item : d) {
	  cout << item << " ";
	  ss << item << " ";
	}
	cout << endl;


	checkTest("testIteratorFundamentals test #7", "2 4 6 8 10 12 14 16 18 20 ", ss.str());
	ss.str("");
}

//This helps with testing, do not modify.
void testIteratorIncrement() {
	//cout << "|||### You need to comment in testIteratorIncrement() when it's ready and remove this ###|||" << endl;
	DoublyLinkedList<int>* d = new DoublyLinkedList<int>;

	//Our test data should have all even numbers from 2 to 20
	for (int i = 2; i <= 20; i += 2) {
	  d->pushBack(i);
	}

	//Get an iterator which points at the beginning of the list
	Iterator<int> iter = d->begin();

	//Test that it does point to the first
	checkTest("testIteratorsIncrement #1", 2, *iter);

	//Test that our Iterator can move forward;
	++iter;
	checkTest("testIteratorsIncrement #2", 4, *iter);


	//Test that our Iterator can move forward again;
	++iter;
	checkTest("testIteratorsIncrement #3", 6, *iter);

	//move it some more
	for (int i = 0; i < 6; i++) {
	  ++iter;
	}
	checkTest("testIteratorsIncrement #4", 18, *iter);

	//Hit the end
	++iter;
	checkTest("testIteratorsIncrement #5", 20, *iter);

	////Verify we move the iterator past the end without crashing
	++iter;
	string didntCrash = "did not crash";
	checkTest("testIteratorsIncrement #6", didntCrash, didntCrash);


	delete d;
}

//This helps with testing, do not modify.
void testIteratorDecrement() {
	//cout << "|||### You need to comment in testIteratorDecrement() when it's ready and remove this###|||" << endl;

	DoublyLinkedList<int>* d = new DoublyLinkedList<int>;

	//Our test data should have all even numbers from 2 to 20
	for (int i = 2; i <= 20; i += 2) {
	  d->pushBack(i);
	}

	//Get an Iterator which points at the end of the list    (Not on the last item, but on the "end" state)
	Iterator<int> iter = d->end();

	--iter;  // We have to do a decrement otherwise the iterator is in the past-the-end state and isn't pointing at a value
	         // Don't comment out this line, even if it makes your test #2 pass.  It will make later tests fail.
	         // If you comment out this line and later contact me for help, then I will drive up to your residence, 
	         // ring your doorbell, and stare at you angrily.  

	//Test that it does point to the first
	checkTest("testIteratorsDecrement #1", 20, *iter);

	////Test that our Iterator can move forward;
	--iter;
	checkTest("testIteratorsDecrement #2", 18, *iter);

	//move it some more
	for (int i = 0; i < 7; i++) {
	  --iter;
	}
	checkTest("testIteratorsDecrement #3", 4, *iter);

	//Hit the end
	--iter;
	checkTest("testIteratorsDecrement #4", 2, *iter);

	//Now go back forward
	++iter;
	checkTest("testIteratorsDecrement #5", 4, *iter);

	delete d;
}

//This helps with testing, do not modify.
void testIterationTricky() {

	cout << "|||### You need to comment in testIterationTricky() when it's ready and remove this###|||" << endl;

	DoublyLinkedList<int> myListOneNode;

	myListOneNode.pushBack(42);
	cout << "TestIterationTricky test #1, the next line should display 42" << endl;
	stringstream ss;
	//see if we can just iterator through one item.
	for (auto i : myListOneNode) {
	  cout << i << " ";
	  ss << i << " ";
	}
	cout << endl;
	checkTest("TestIterationTricky test #1", "42 ", ss.str());
	ss.str("");

	DoublyLinkedList<int> myListEmpty;
	cout << "TestIterationTricky test #2, the next line shouldn't display anything" << endl;
	//see if we can just iterator through one item.
	for (auto i : myListEmpty) {
	  cout << i << " ";
	  ss << i << " ";
	}
	cout << endl;
	checkTest("TestIterationTricky test #2", "", ss.str());
	ss.str("");
}



//This helps with testing, do not modify.
void testAlgorithms() {
	//cout << "|||### You need to comment in testAlgorithms() when it's ready and remove this###|||" << endl;

	DoublyLinkedList<int> myList;

	//Our test data should have all even numbers from 2 to 20
	for (int i = 2; i <= 6; i += 2) {
	  myList.pushBack(i);
	}
	myList.pushBack(100);
	for (int i = 8; i <= 12; i += 2) {
	  myList.pushBack(i);
	}
	myList.pushBack(100);
	for (int i = 14; i <= 20; i += 2) {
	  myList.pushBack(i);
	}
	stringstream ss;
	cout << "testAlgorithms test #1, this should display 2 4 6 100 8 10 12 100 14 16 18 20." << endl;
	for (auto i : myList) {
	  cout << i << " ";
	  ss << i << " ";
	}
	cout << endl;
	checkTest("testAlgorithms test #1", "2 4 6 100 8 10 12 100 14 16 18 20 ", ss.str());
	ss.str("");

	//Test the STL reverse algorithm on our iterator
	cout << "testAlgorithms test #2, this should display 20 18 16 14 100 12 10 8 100 6 4 2." << endl;
	std::reverse(myList.begin(), myList.end());
	for (auto i : myList) {
	  cout << i << " ";
	  ss << i << " ";
	}
	cout << endl;
	checkTest("testAlgorithms test #2", "20 18 16 14 100 12 10 8 100 6 4 2 ", ss.str());
	ss.str("");

	//Get it back in ascending order using the STL reverse algorithm
	std::reverse(myList.begin(), myList.end());
	for (auto i : myList) {
	  cout << i << " ";
	  ss << i << " ";
	}
	cout << endl;
	checkTest("testAlgorithms test #3", "2 4 6 100 8 10 12 100 14 16 18 20 ", ss.str());
	ss.str("");

	// Try a custom assignmentReverse function

	assignmentReverse(myList.begin(), myList.end());
	for (auto i : myList) {
	  cout << i << " ";
	  ss << i << " ";
	}
	cout << endl;
	checkTest("testAlgorithms test #4", "20 18 16 14 100 12 10 8 100 6 4 2 ", ss.str());
	ss.str("");

	//Get it back in ascending order using the STL reverse algorithm
	assignmentReverse(myList.begin(), myList.end());
	for (auto i : myList) {
	  cout << i << " ";
	  ss << i << " ";
	}
	cout << endl;

	checkTest("testAlgorithms test #5", "2 4 6 100 8 10 12 100 14 16 18 20 ", ss.str());
	ss.str("");

	// Test assignmentReverse on an STL container:


	list<int> stlList;

	//Our test data should have all even numbers from 2 to 20
	for (int i = 2; i <= 6; i += 2) {
	  stlList.push_back(i);
	}
	stlList.push_back(100);
	for (int i = 8; i <= 12; i += 2) {
	  stlList.push_back(i);
	}
	stlList.push_back(100);
	for (int i = 14; i <= 20; i += 2) {
	  stlList.push_back(i);
	}
	for (auto i : stlList) {
	  cout << i << " ";
	  ss << i << " ";
	}
	cout << endl;
	checkTest("testAlgorithms test #6", "2 4 6 100 8 10 12 100 14 16 18 20 ", ss.str());
	ss.str("");

	// Try a custom assignmentReverse function

	assignmentReverse(stlList.begin(), stlList.end());
	for (auto i : stlList) {
	  cout << i << " ";
	  ss << i << " ";
	}
	cout << endl;
	checkTest("testAlgorithms test #7", "20 18 16 14 100 12 10 8 100 6 4 2 ", ss.str());
	ss.str("");


}



//This helps with testing, do not modify.
void testLambda() {
	cout << "|||### You need to comment in testLambda() when it's ready and remove this###|||" << endl;

	DoublyLinkedList<string> myWords;

	myWords.pushBack("bob");
	myWords.pushBack("racecar");
	myWords.pushBack("peep");
	myWords.pushBack("redder");
	myWords.pushBack("sells");
	myWords.pushBack("pneumonoultramicroscopicsilicovolcanoconiosis");
	myWords.pushBack("Was it a car or a cat I saw?");
	myWords.pushBack("Madam, in Eden, I'm Adam");
	myWords.pushBack("A nut for a jar of tuna");
	myWords.pushBack("Borrow or rob?");
	myWords.pushBack("This is a palindrome!");


	// Lets search for only palindromes

	// Prepare a container to hold output.  
	vector<string> output(11);

	// TODO:

	 //Utilize an STL algorithm std::copy_if with a lambda expression to filter out all palindromes into the vector called output
	 //The lambda expression captures nothing
	 //The lambda expression needs a single parameter, a const string reference.  
	 //The code body of the lambda expression needs to return a boolean.  True if the string is a palindrome, false if not.
	 //Note that you must remove all non-letter characters and then turn all upper-case to lower-case.  After that you
	 //  can easily test if the string is a palindrome

	auto it = std::copy_if(myWords.begin(), //lambda expressions are essentially ANONYMOUS function objects, right at the location where its invoked.
		myWords.end(),
		output.begin(),
		/* TODO: put lambda here
		*captures nothing
		const string reference parameter
		return boolean if the string is a palendrome or not*/
			[](const string& theString) -> bool {
				//code inspired by geeksForGeeks, utilizing ASCII values -> https://www.geeksforgeeks.org/remove-characters-alphabets-string/
				bool isValid = true;
				string newString; //remove special characters
				string reversedString;
				for (int i = 0; i < theString.size(); i++) {
					if (//if the ASCII value of the current char in string is Alphabetic.
						theString[i] >= 'A' || theString[i] <= 'Z' &&
						theString[i] >= 'a' || theString[i] <= 'z') {
						//now convert all to lowercase
						newString += (tolower(theString[i]));
					}
				}
				for (int i = newString.size(); i > -1; i--) { //reverse string
					reversedString += newString[i];
				}
				//now determine if the newString is a palendrome
				return (reversedString == newString);
			}
		);

	output.resize(std::distance(output.begin(), it));  // Shrink output to new size
	std::stringstream ss;
	for (auto& str : output) {
		ss << str << "|";
	}
	checkTest("testLambda test #1", "bob|racecar|peep|redder|Was it a car or a cat I saw?|Madam, in Eden, I'm Adam|A nut for a jar of tuna|Borrow or rob?|", ss.str());

}

void pressAnyKeyToContinue() {
	cout << "Press enter to continue...";
	cin.get();
}

int main() {

	cout << "This first test can run forever until you get operators *, != and ++ implemented." << endl;
	//pressAnyKeyToContinue();

	testIteratorFundamentals();
	pressAnyKeyToContinue();

	testIteratorIncrement();
	pressAnyKeyToContinue();

	testIteratorDecrement();
	pressAnyKeyToContinue();

	testIterationTricky();
	pressAnyKeyToContinue();

	testAlgorithms();
	pressAnyKeyToContinue();

	testLambda();
	pressAnyKeyToContinue();

	return 0;
}