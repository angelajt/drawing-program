/*
 * LinkedStack.tpp
 *
 *  Created on: Oct 15, 2022
 *      Author: angela
 */


LinkedStack::LinkedStack() : head(nullptr), last(nullptr) { }

/* destructor
 *
 * asymptotic analysis: O(n)
 */
LinkedStack::~LinkedStack()
{
	clear();
}

/*
 * copy() takes a LinkedStack and copies its contents to the current stack.
 *
 * asymptotic analysis: O(n)
 */
void LinkedStack::copy(const LinkedStack& copyObj){
    this->length = copyObj.length;
    head = last = nullptr;

    if (this->length > 0) {
        head = new Node(copyObj.head->value);
        Node* curr = head;
        Node* copyCurr = copyObj.head->next;

        while (copyCurr != nullptr) {
            Node* n = new Node(copyCurr->value, nullptr, curr);
            curr->next = n;
            curr = n;
            copyCurr = copyCurr->next;
        }

        last = curr;
    }
}

/*
 * save() takes a string filename and saves the contents of the stack to the
 * file.
 *
 * asymptotic analysis: O(n)
 */
void LinkedStack::save(string filename) {
	fstream drawingData;

	// open the file
	drawingData.open(filename, ios::out);
	if (drawingData.fail()) {
		throw string("couldn't open file for saving");
	}

	for (int i = 0; i < this->length; i++) {

		// rotate stack to access each element
		rotate(LEFT);
		Square s = peek();

		// output each square to the file
		drawingData << s << endl;
	}

	// close the file
	drawingData.close();
}

/*
 * load() takes a string filename and populates the stack based on the contents
 * of the file.
 *
 * asymptotic analysis: O(n) where n depends on the lines of the file
 */
void LinkedStack::load(string filename) {

	// clear the stack so we aren't just loading on top of an existing drawing
	clear();

	fstream drawingData;

	// open the file
	drawingData.open(filename, ios::in);
	if (drawingData.fail()) {
		throw string("couldn't open file for loading");
	}

	// iterate over every line in the file
	while ((!drawingData.eof())) {

		// put the line into a string
		string line, word;
		getline(drawingData, line);

		// ignore any spaces or newlines at the end of the file
		if (line == "" || isblank(line.at(0))) {
			continue;
		}

		// convert the line into a square
		Square s;
		try {
			s = loadLine(line);
		} catch (string& err) {
			throw err;
		}

		// push the square to the stack
		this->push(s);
	}

	// close the file
	drawingData.close();
}

/* copy constructor implementing copy()
 *
 * asymptotic analysis: O(n)
 */
LinkedStack::LinkedStack(const LinkedStack& copyObj) {
    copy(copyObj);
}

/* assignment operator overload implementing copy()
 *
 * asymptotic analysis: O(n)
 */
LinkedStack& LinkedStack::operator=(const LinkedStack& rightObj) {
	if (this != &rightObj) {
		clear();
		copy(rightObj);
	}
	return *this;
}

/*
 * clear() removes all of the stack's elements and updates the length to 0.
 *
 * asymptotic analysis: O(n)
 */
 void LinkedStack::clear() {
	Node* prev;

	// iterate over every node, deleting the previous
    while (head != nullptr) {
    	prev = head;
        head = head->next;
        delete prev;
        prev = nullptr;
    }

    // ensure last isn't pointing to bad address
    last = nullptr;

    this->length = 0;
}

/*
 * getLength() returns the length.
 *
 * asymptotic analysis: O(1)
 */
int LinkedStack::getLength() const {
	return this->length;
}

/*
 * isEmpty() returns true if the length is 0.
 *
 * asymptotic analysis: O(1)
 */
bool LinkedStack::isEmpty() const {
	return this->length == 0;
}

/*
 * peek() returns the element at the top of the stack.
 *
 * asymptotic analysis: O(1)
 */
Square LinkedStack::peek() const {
	if (isEmpty()) {
		throw string("peek() error: stack is empty");
	}
	return head->value;
}

/*
 * pop() removes the element from the top of the stack.
 *
 * asymptotic analysis: O(1)
 */
void LinkedStack::pop() {
	if (isEmpty()) {
		throw string("pop() error: stack is empty");
	}

	Node* old = head;
	head = head->next;
	delete old;
	this->length--;

	if (!isEmpty()) {
		head->prev = nullptr;
	}
}

/*
 * push() takes an element and adds it to the top of the stack, updating the
 * length.
 *
 * asymptotic analysis: O(1)
 */
void LinkedStack::push(const Square& elem) {
	Node* n = new Node(elem, head, nullptr);
	head = n;

	if (isEmpty()) {
		last = head;
	} else {
		n->next->prev = n;
	}

	this->length++;
}

/*
 * rotate() rotates the stack.
 * LEFT: moves bottom to top.
 * RIGHT: moves top to bottom.
 *
 * if the stack is empty or has only 1 element, don't throw an exception,
 * so that the TUI can safely iterate over every element in a stack regardless
 * of size.
 *
 * asymptotic analysis: O(1)
 */
void LinkedStack::rotate(typename Stack::Direction dir) {
	if (isEmpty() || this->length == 1) {
		return;
	}

	if (dir == Stack::RIGHT) {
		last->next = head;
		head->prev = last;
		last = head;
		head = head->next;
		head->prev = nullptr;
		last->next = nullptr;
	} else {
		last->next = head;
		head->prev = last;
		head = last;
		last = last->prev;
		last->next = nullptr;
		head->prev = nullptr;
	}
}
