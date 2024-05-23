//Copyright 2021, Bradley Peterson, Weber State University, All rights reserved. (9/2021)
#include <sstream>
#include <chrono>
#include <iostream>
#include <set>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::stringstream;
using std::set;

class DestructorTester {
public:
	static unsigned int getCount() {
		return count;
	}
	static unsigned int getTotalCopyCalls() {
		return totalCopyCalls;
	}
	DestructorTester() {
		count++;
	}
	DestructorTester(const DestructorTester& obj) {
		count++;
		totalCopyCalls++;
	}
	void operator=(const DestructorTester& obj) {
		// Not a constructor, so no new object is created here.  No need to increment count.
		totalCopyCalls++;
	}
	~DestructorTester() {
		count--;
	}
private:
	static unsigned int count;
	static unsigned int totalCopyCalls;
};
unsigned int DestructorTester::count = 0;
unsigned int DestructorTester::totalCopyCalls = 0;

//******************
//The Node class
//******************
template <typename T>
class Node { //NODES, INSIDE LINKED LIST
public:
	T data{};
	Node<T>* link{ nullptr }; //the pointer that points to the next node
};

//******************
// The linked list base class
//******************
template <typename T>
class LinkedListBase {
public:
	~LinkedListBase();
	string getStringFromList();
	T getFifthElement() const { cerr << "Error: You didn't override this base class method yet" << endl; T temp{}; return temp; }
	void insertNewFifthElement(const T& data) { cerr << "Error: You didn't override this base class method yet" << endl; }
	void deleteFifthElement() { cerr << "Error: You didn't override this base class method yet" << endl; }
	void swapFifthAndSeventhElement() { cerr << "Error: You didn't override this base class method yet" << endl; }
	T getLast() const;
	void pushFront(const T& data);
	void pushBack(const T& data);
	void popFront();
	void popBack();

protected: //DATA MEMBERS
	Node<T>* head{ nullptr }; //points to previous item
	Node<T>* tail{ nullptr }; //points to next item
	unsigned int count{ 0 };
};

template <typename T>
LinkedListBase<T>::~LinkedListBase() {
	Node<T>* temp = head;
	while (temp) {
		head = head->link;
		delete temp;
		temp = head;
	}
}
//This method helps return a string representation of all nodes in the linked list, do not modify.
template <typename T>
string LinkedListBase<T>::getStringFromList() {
	stringstream ss;
	if (!this->head) {
		ss << "The list is empty.";
	}
	else {

		Node<T>* currentNode = this->head;
		ss << currentNode->data;
		currentNode = currentNode->link;

		while (currentNode) {
			ss << " " << currentNode->data;
			currentNode = currentNode->link;
		};
	}
	return ss.str();
}

template <typename T>
T LinkedListBase<T>::getLast() const {
	if (this->tail) {
		return this->tail->data;
	}
	else {
		throw 1;
	}
}
template <typename T>
void LinkedListBase<T>::pushFront(const T& data) {

	if (!head) {
		// Scenario: The list is empty
		Node<T>* temp = new Node<T>();
		temp->data = data;
		this->head = temp;
		this->tail = temp;
		count++;
	}
	else {
		// Scenario: One or more nodes
		Node<T>* temp = new Node<T>();
		temp->data = data;
		temp->link = this->head;
		this->head = temp;
		count++;
	}
}

template <typename T>
void LinkedListBase<T>::pushBack(const T& data) {
	if (!head) {
		//Scenario: The list is empty
		Node<T>* temp = new Node<T>();
		temp->data = data;
		this->head = temp;
		this->tail = temp;
		count++;
	}
	else {
		Node<T>* temp = new Node<T>();
		temp->data = data;
		this->tail->link = temp;
		this->tail = temp;
		count++;
	}
}

template <typename T>
void LinkedListBase<T>::popFront() {

	if (!head) {
		// Scenario: The list is empty
		cout << "The list was already empty" << endl;
		return;
	}
	else if (this->head == this->tail) {
		// Scenario: One node list
		this->tail = nullptr;
		delete this->head;
		this->head = nullptr;
		count--;
	}
	else {
		// Scenario: General, at least two or more nodes
		Node<T>* temp = nullptr;
		temp = this->head->link;
		delete this->head;
		this->head = temp;
		count--;
	}
}

template <typename T>
void LinkedListBase<T>::popBack() {
	if (!this->head) {
		// Scenario: The list is empty
		cout << "The list was already empty" << endl;
		return;
	}
	else if (this->head == this->tail) {
		// Scenario: One node list
		this->tail = nullptr;
		delete this->head;
		this->head = nullptr;
		count--;
	}
	else {
		// Scenario: General, at least two or more nodes
		Node<T>* temp = nullptr;
		temp = head;

		while (temp->link != this->tail) {
			temp = temp->link; // This is like i++;
		}

		// temp is now at the second to tail node
		delete this->tail;
		this->tail = temp;
		this->tail->link = nullptr;
		count--;
	}
}


//**********************************
//Write your code below here
//**********************************

template <typename T>
class SinglyLinkedList : public LinkedListBase<T> { //WORK CODE, inherits datamembers from base class LinkedListBase<T>
public:
	T getFifthElement() const; //returns data at fifth node, throw std oor if no fifth
	void insertNewFifthElement(const T& value); //inserts node containing data between 4 and 5, if less than 4, dont insert
	void deleteFifthElement(); //points node 6 to node 4.
	void swapFifthAndSeventhElement(); //rearrange pointers to 5th and 7th nodes, cannot swap data.
};

//TODO: Define your methods here.
template<typename T>
T SinglyLinkedList<T>::getFifthElement() const
{
	if (this->count < 5) {
		throw std::out_of_range("Not enough elements");
	}
	else {
		Node<T>* currentNode = this->head; //beginning of list
		for (int i = 1; i < 5; i++) { //iterate down the list 5 times
			currentNode = currentNode->link; //set ptr to next item
		}
		return currentNode->data; //return data after 5 iterations
	}
}

template<typename T>
void SinglyLinkedList<T>::insertNewFifthElement(const T& value)
{
	if (this->count == 4) { //4 items, just insert at the end
		this->pushBack(value);
	}
	else if (this->count < 4) { //less than 4 items, display error and do nothing
		cout << "Not enough elements, cannot insert new fifth" << endl;
	}
	else { //more than 4 items, general operation
		Node<T>* currentNode = this->head;
		Node<T>* fourthNode = nullptr;
		for (int i = 1; i < 5; i++) {
			if (i == 4) { //when iterating over the FOURTH item
				fourthNode = currentNode;
			}
			currentNode = currentNode->link; //go to next item
		}
		Node<T>* newNode = new Node<T>();
		fourthNode->link = newNode; //sets link to address of new node
		newNode->data = value; //set data = value passed
		newNode->link = currentNode; //sets newNodes link to currentNode, now the 6th element.
		this->count++;
	}
}

template<typename T>
void SinglyLinkedList<T>::deleteFifthElement()
{
	Node<T>* currentNode = this->head; //5th to be deleted
	Node<T>* fourthNode = nullptr; //4th to change link
	for (int i = 1; i < 5; i++) { //iterate to find 4th and 5th element
		if (i == 4) { //fourth item
			fourthNode = currentNode;
		}
		currentNode = currentNode->link;
	}
	fourthNode->link = currentNode->link;
	currentNode->link = nullptr;
	delete currentNode; //release the object now that its out of use
	this->count--;//one less object
}

template<typename T>
void SinglyLinkedList<T>::swapFifthAndSeventhElement()
{
	Node<T>* fourthPtr = nullptr; //set link on fourth equal to 7
	Node<T>* fifthPtr = nullptr; //set link on fifth equal to seventh
	Node<T>* sixthPtr = nullptr; //set link on sixth equal to 
	Node<T>* seventhPtr = this->head; //iterative ptr, set link on seventh equal to fifth
	for (int i = 1; i < 7; i++) {
		if (i == 4) { //fourth ptr
			fourthPtr = seventhPtr;
		}
		else if (i == 5) { //fifth ptr
			fifthPtr = seventhPtr;
		}
		else if (i == 6) { //sixth ptr
			sixthPtr = seventhPtr;
		} //the remaining iterative ptr will be the 7th ptr.
		seventhPtr = seventhPtr->link;
	}
	/*
	4>5>6>7 original structure
	4>7>6>5 final structure
	*/
	fourthPtr->link = seventhPtr;
	seventhPtr->link = sixthPtr;
	sixthPtr->link = fifthPtr;
}

//**********************************
//Write your code above here
//**********************************


//This helps with testing, do not modify.
bool checkTest(string testName, string whatItShouldBe, string whatItIs) {

	if (whatItShouldBe == whatItIs) {
		cout << "Passed " << testName << endl;
		return true;
	}
	else {
		cout << "****** Failed test " << testName << " ****** " << endl << "     Output was " << whatItIs << endl << "     Output should have been " << whatItShouldBe << endl;
		return false;
	}
}

//This helps with testing, do not modify.
bool checkTest(string testName, int whatItShouldBe, int whatItIs) {

	if (whatItShouldBe == whatItIs) {
		cout << "Passed " << testName << endl;
		return true;
	}
	else {
		cout << "****** Failed test " << testName << " ****** " << endl << "     Output was " << whatItIs << endl << "     Output should have been " << whatItShouldBe << endl;
		return false;
	}
}

//This helps with testing, do not modify.
bool checkTestMemory(string testName, int whatItShouldBe, int whatItIs) {

	if (whatItShouldBe == whatItIs) {
		cout << "Passed " << testName << endl;
		return true;
	}
	else {
		cout << "***Failed test " << testName << " *** " << endl << "  You lost track of " << whatItIs << " bytes in memory!" << endl;
		return false;
	}
}

//This helps with testing, do not modify.
void testGetFifthElement() {
	SinglyLinkedList<int>* si = new SinglyLinkedList<int>;
	for (int i = 10; i < 20; i++) {
		si->pushBack(i);
	}

	//Test just to make sure the data went in the list. 
	checkTest("testGetFifthElement #1", "10 11 12 13 14 15 16 17 18 19", si->getStringFromList());

	//Test retrieving item. 
	int item = si->getFifthElement();
	checkTest("testGetFifthElement #2", 14, item);
	delete si;

	si = new SinglyLinkedList<int>;
	for (int i = 10; i < 15; i++) {
		si->pushBack(i);
	}
	//Test just to make sure the data went in the list. 
	checkTest("testGetFifthElement #3", "10 11 12 13 14", si->getStringFromList());

	//Test retrieving item. 
	item = si->getFifthElement();
	checkTest("testGetFifthElement #4", 14, item);
	delete si;


	si = new SinglyLinkedList<int>;
	for (int i = 10; i < 14; i++) {
		si->pushBack(i);
	}
	//Test just to make sure the data went in the list. 
	checkTest("testGetFifthElement #5", "10 11 12 13", si->getStringFromList());

	//Try to access out of bounds.  
	string caughtError = "";
	try {
		item = si->getFifthElement();
	}
	catch (std::out_of_range & oor) {
		caughtError = "caught";
	}
	checkTest("testGetFifthElement #6", "caught", caughtError);
	delete si;

	SinglyLinkedList<string>* ss = new SinglyLinkedList<string>;
	ss->pushBack("Multi Pass");
	ss->pushBack("Lelu Dallas");
	ss->pushBack("BIG BADA BOOM");
	ss->pushBack("Bruce Willis");
	ss->pushBack("Fried Chicken");
	ss->pushBack("EEEAAAAAAAeeeaaaaaEEeeAAAEEaaaaAA");
	checkTest("testGetFifthElement #7", "Fried Chicken", ss->getFifthElement());
	delete ss;

	SinglyLinkedList<DestructorTester>* dt = new SinglyLinkedList<DestructorTester>();
	for (int i = 0; i < 10; i++) {
		dt->pushBack(DestructorTester());
	}
	dt->getFifthElement();
	if (DestructorTester::getCount() == 10) {
		cout << "Passed testGetFifthElement #8" << endl;
	}
	else {
		cout << "***Failed test testGetFifthElement #8 *** " << endl << "   You have a memory leak. " << endl;
	}

	delete dt;
	if (DestructorTester::getCount() == 0) {
		cout << "Passed testGetFifthElement #9" << endl;
	}
	else {
		cout << "***Failed test testGetFifthElement #9 *** " << endl << "   You have a memory leak. " << endl;
	}
}


//This helps with testing, do not modify.
void testInsertNewFifthElement() {

	SinglyLinkedList<int>* si = new SinglyLinkedList<int>;
	for (int i = 10; i < 20; i++) {
		si->pushBack(i);
	}

	//Test just to make sure the data went in the list. 
	checkTest("testInsertNewFifthElement #1", "10 11 12 13 14 15 16 17 18 19", si->getStringFromList());

	//Test inserting an item
	si->insertNewFifthElement(97);
	checkTest("testInsertNewFifthElement #2", "10 11 12 13 97 14 15 16 17 18 19", si->getStringFromList());
	delete si;

	si = new SinglyLinkedList<int>;
	for (int i = 10; i < 15; i++) {
		si->pushBack(i);
	}
	//Test just to make sure the data went in the list. 
	checkTest("testInsertNewFifthElement #3", "10 11 12 13 14", si->getStringFromList());

	//Test inserting an item
	si->insertNewFifthElement(97);
	checkTest("testInsertNewFifthElement #4", "10 11 12 13 97 14", si->getStringFromList());
	delete si;

	si = new SinglyLinkedList<int>;
	for (int i = 10; i < 14; i++) {
		si->pushBack(i);
	}
	//Test just to make sure the data went in the list. 
	checkTest("testInsertNewFifthElement #5", "10 11 12 13", si->getStringFromList());

	//Test inserting an item
	si->insertNewFifthElement(97);
	checkTest("testInsertNewFifthElement #6", "10 11 12 13 97", si->getStringFromList());
	checkTest("testInsertNewFifthElement #7", 97, si->getLast());
	delete si;



	// Now test inserting an invalid option
	si = new SinglyLinkedList<int>;
	for (int i = 10; i < 13; i++) {
		si->pushBack(i);
	}
	si->insertNewFifthElement(1000);
	//Test just to make sure the data didn't go in at all and didn't crash.
	checkTest("testInsertNewFifthElement #8", "10 11 12", si->getStringFromList());

	delete si;

	SinglyLinkedList<DestructorTester>* dt = new SinglyLinkedList<DestructorTester>();
	for (int i = 0; i < 10; i++) {
		dt->pushBack(DestructorTester());
	}
	dt->insertNewFifthElement(DestructorTester());
	if (DestructorTester::getCount() == 11) {
		cout << "Passed testInsertNewFifthElement #9" << endl;
	}
	else {
		cout << "***Failed test testInsertNewFifthElement #9 *** " << endl << "   You have a memory leak. " << endl;
	}

	delete dt;
	if (DestructorTester::getCount() == 0) {
		cout << "Passed testInsertNewFifthElement #10" << endl;
	}
	else {
		cout << "***Failed test testInsertNewFifthElement #10 *** " << endl << "   You have a memory leak. " << endl;
	}

}

//This helps with testing, do not modify.
void testDeleteFifthElement() {
	// Note from the instructor: Please do not delete the actual movie.  It's very good and shouldn't be removed.

	SinglyLinkedList<int>* si = new SinglyLinkedList<int>;
	for (int i = 10; i < 20; i++) {
		si->pushBack(i);
	}

	//Test just to make sure the data went in the list. 
	checkTest("testDeleteFifthElement #1", "10 11 12 13 14 15 16 17 18 19", si->getStringFromList());

	//Test deleting an item
	si->deleteFifthElement();
	checkTest("testDeleteFifthElement #2", "10 11 12 13 15 16 17 18 19", si->getStringFromList());
	delete si;

	si = new SinglyLinkedList<int>;
	for (int i = 10; i < 16; i++) {
		si->pushBack(i);
	}
	//Test just to make sure the data went in the list. 
	checkTest("testDeleteFifthElement #3", "10 11 12 13 14 15", si->getStringFromList());

	//Test deleting an item
	si->deleteFifthElement();
	checkTest("testDeleteFifthElement #4", "10 11 12 13 15", si->getStringFromList());
	delete si;

	si = new SinglyLinkedList<int>;
	for (int i = 10; i < 15; i++) {
		si->pushBack(i);
	}
	//Test just to make sure the data went in the list. 
	checkTest("testDeleteFifthElement #5", "10 11 12 13 14", si->getStringFromList());
	checkTest("testDeleteFifthElement #6", 14, si->getLast());

	//Test deleting an item
	si->deleteFifthElement();
	checkTest("testDeleteFifthElement #7", "10 11 12 13", si->getStringFromList());
	checkTest("testDeleteFifthElement #8", 13, si->getLast());
	delete si;

	SinglyLinkedList<DestructorTester>* dt = new SinglyLinkedList<DestructorTester>();
	for (int i = 0; i < 10; i++) {
		dt->pushBack(DestructorTester());
	}
	dt->deleteFifthElement();
	if (DestructorTester::getCount() == 9) {
		cout << "Passed testDeleteFifthElement #9" << endl;
	}
	else {
		cout << "***Failed test testDeleteFifthElement #9 *** " << endl << "   You have a memory leak. " << endl;
	}

	delete dt;
	if (DestructorTester::getCount() == 0) {
		cout << "Passed testDeleteFifthElement #10" << endl;
	}
	else {
		cout << "***Failed test testDeleteFifthElement #10 *** " << endl << "   You have a memory leak. " << endl;
	}

}

//This helps with testing, do not modify.
void testSwapFifthAndSeventhElement() {
	// Note from the instructor: Please do not delete the actual movie.  
	// It's very good and shouldn't be removed.

	SinglyLinkedList<int>* si = new SinglyLinkedList<int>;
	for (int i = 10; i < 20; i++) {
		si->pushBack(i);
	}

	//Test just to make sure the data went in the list. 
	checkTest("testSwapFifthAndSeventhElement #1", "10 11 12 13 14 15 16 17 18 19", si->getStringFromList());

	//Test swapping an item
	si->swapFifthAndSeventhElement();
	checkTest("testSwapFifthAndSeventhElement #2", "10 11 12 13 16 15 14 17 18 19", si->getStringFromList());

	delete si;

	si = new SinglyLinkedList<int>;
	for (int i = 10; i < 17; i++) {
		si->pushBack(i);
	}

	//Test just to make sure the data went in the list. 
	checkTest("testSwapFifthAndSeventhElement #3", "10 11 12 13 14 15 16", si->getStringFromList());

	//Test swapping an item
	si->swapFifthAndSeventhElement();
	checkTest("testSwapFifthAndSeventhElement #4", "10 11 12 13 16 15 14", si->getStringFromList());
	checkTest("testSwapFifthAndSeventhElement #5", 14, si->getLast());
	delete si;


	SinglyLinkedList<DestructorTester>* dt = new SinglyLinkedList<DestructorTester>();
	for (int i = 0; i < 10; i++) {
		dt->pushBack(DestructorTester());
	}
	unsigned int beforeTotalCopyCalls = DestructorTester::getTotalCopyCalls();
	dt->swapFifthAndSeventhElement();
	unsigned int afterTotalCopyCalls = DestructorTester::getTotalCopyCalls();
	if (beforeTotalCopyCalls == afterTotalCopyCalls) {
		cout << "Passed testSwapFifthAndSeventhElement #6" << endl;
	}
	else {
		cout << "***Failed test testSwapFifthAndSeventhElement #6 *** " << endl << "   You didn't move the pointers around, you copied values " << (afterTotalCopyCalls - beforeTotalCopyCalls) << " times." << endl;
	}

	if (DestructorTester::getCount() == 10) {
		cout << "Passed testSwapFifthAndSeventhElement #7" << endl;
	}
	else {
		cout << "***Failed test testSwapFifthAndSeventhElement #7 *** " << endl << "   You have a memory leak. " << endl;
	}

	delete dt;
	if (DestructorTester::getCount() == 0) {
		cout << "Passed testSwapFifthAndSeventhElement #8" << endl;
	}
	else {
		cout << "***Failed test testSwapFifthAndSeventhElement #8 *** " << endl << "   You have a memory leak. " << endl;
	}

}


void pressAnyKeyToContinue() {
	cout << "Press enter to continue...";

	cin.get();

}


int main() {

	testGetFifthElement();

	testInsertNewFifthElement();

	//pressAnyKeyToContinue();

	testDeleteFifthElement();

	testSwapFifthAndSeventhElement();

	pressAnyKeyToContinue();

	return 0;
}
