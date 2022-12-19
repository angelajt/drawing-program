/*
 * constructor for an empty sorted list.
 *
 * asymptotic analysis: O(1)
 */
SortedList::SortedList()
: head(nullptr), length(0) {}

/*
 * copy constructor for a sorted list.
 *
 * asymptotic analysis: O(n)
 */
SortedList::SortedList(const SortedList& copyObj) {
    copy(copyObj);
}

/*
 * destructor for a sorted list.
 *
 * asymptotic analysis: O(n)
 */
SortedList::~SortedList() {
    clear();
}

/*
 * assignment operator for a sorted list, utilizing the copy constructor.
 *
 * asymptotic analysis: O(1)
 */
SortedList& SortedList::operator=(const SortedList& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}


/*
 * populate() takes a vector of strings, sorts the vector, and appends each
 * element of the vector to an empty sorted list. this is the only function
 * that uses append(). technically the way insert() works, we don't need an
 * append() function or a sorting algorithm at all, but for the sake of this
 * project i will be using quicksort to populate the linked list.
 *
 * asymptotic analysis:
 * - best case: O(1)
 * - average: O(n*log(n))
 * - worse case: O(n^2)
 */
void SortedList::populate(vector<string>& fileNames) {
	quicksort(fileNames, 0, fileNames.size() - 1);
	clear();
	for (int i = 0; i < fileNames.size(); i++) {
		append(fileNames.at(i));
	}
}

/*
 * append() takes a string, converts it to a node's value, and adds that node
 * to the end of the linked list. this function is private, and not called
 * outside of populate(), because this is a sorted list so new nodes are
 * typically added via insert() to maintain sorted order.
 *
 * asymptotic analysis where list is empty: O(1)
 * asymptotic analysis where list is populated: O(n)
 */
void SortedList::append(string elem) {
    Node* n = new Node(elem, nullptr);

    if (head == nullptr) {
        head = n;
		this->length++;
    } else {
    	appendRec(n, head);
    }
}

/*
 * appendRec() is a recursive function takes the new node, and a node
 * representing the current node in the sorted list that we are iterating
 * over. if the current node is the last node in the list, set its next value
 * to the new node and update the length of the list. otherwise, recurse into
 * the next node in the list.
 *
 * asymptotic analysis where base case is met (end of list): O(1)
 * asymptotic analysis where base case is not met: O(n)
 */
void SortedList::appendRec(Node* n, Node* curr) {
	if (curr->next == nullptr) {
		curr->next = n;
		this->length++;
		return;
	}
	appendRec(n, curr->next);
}

/*
 * swap() takes a reference to a vector of strings, and two integers that
 * represent positions in the vector, swapping the strings at these two
 * positions.
 *
 * asymptotic analysis: O(1)
 */
void swap(vector<string>& fileNames, int i, int j) {
    string temp    = fileNames.at(i);
    fileNames.at(i) = fileNames.at(j);
    fileNames.at(j) = temp;
}

/*
 * quicksort() is a recursive function that takes a vector of strings and
 * two integers that represent positions in the vector, sorting the vector
 * using the quicksort algorithm.
 *
 * asymptotic analysis where base case is met: O(1)
 * asymptotic analysis where base case is not met:
 * - best case: O(1)
 * - average: O(n*log(n))
 * - worse case: O(n^2)
 */
void quicksort(vector<string>& fileNames, int left, int right) {

	// base case
	if (left >= right) return;

	// pivot index is middle index
	int pivot = left + (right - left) / 2;

	// swap pivot with last record of array
	swap(fileNames, pivot, right);

	int x = left - 1;
	int y = right;
	while (x < y) {
		do {
			// increment x while its value is smaller than the pivot
			x++;
		} while (fileNames.at(x) < fileNames.at(right));

		do {
			// increment y while its value is greater than the pivot,
			// and while x < y
			y--;
		} while ((fileNames.at(y) > fileNames.at(right)) && (x < y));

		// swap x and y if x is smaller than y
		if (x < y) swap(fileNames, x, y);
	}

	// swap x's value with the pivot
	swap(fileNames, x, right);

	// perform quicksort on the two partitions outside the pivot
	quicksort(fileNames, left, y);
	quicksort(fileNames, x + 1, right);
}

/*
 * clear() empties the list and resets the length to 0
 *
 * asymptotic analysis: O(n)
 */
void SortedList::clear() {
	clearRec();
    this->length = 0;
}

/*
 * clearRec() is a recursive function which iterates over the list and deletes
 * each node before recursing into the next node
 *
 * asymptotic analysis where base case is met: O(1)
 * asymptotic analysis where base case is not met: O(n)
 */
void SortedList::clearRec() {
	// base case: list is empty
    if (head == nullptr) {
        return;
    }

    // delete the head node
	Node* prev = head;
    head = head->next;
    delete prev;

    // recurse into the next node
    clearRec();
}

/*
 * copy() takes a sorted list and copies its contents and links to the current
 * sorted list.
 *
 * this is not used by the TUI, but it is useful for debugging purposes.
 *
 * asymptotic analysis if empty: O(1)
 * asymptotic analysis if not empty: O(n)
 */
void SortedList::copy(const SortedList& copyObj) {
	if (copyObj.head == nullptr) {
		head = nullptr;
		return;
	}

	head = new Node(copyObj.head->value);
    this->length++;

    copyRec(head, copyObj.head->next);
}

/*
 * copyRec() is a recursive function that takes two nodes and copies one node
 * to the other's next, before recursing into the nodes' respective next nodes.
 *
 * this is not used by the TUI, but it is useful for debugging purposes.
 *
 * asymptotic analysis where base case is met: O(1)
 * asymptotic analysis where base case is not met: O(n)
 */
void SortedList::copyRec(Node* curr, Node* copyNext) {
	// nothing left to copy
    if (copyNext == nullptr) {
    	return;
    }

    curr->next = new Node(copyNext->value);
    this->length++;

    copyRec(curr->next, copyNext->next);
}

/*
 * getElement() takes a position and returns the value of the node in that
 * position.
 *
 * asymptotic analysis if invalid: O(1)
 * asymptotic analysis if valid: O(n)
 */
string SortedList::getElement(int position) const {
    if (position < 0 || position >= this->length) {
        throw string("getElement: error, position out of bounds");
    }

	return getElementRec(position, head);
}

/*
 * getElementRec() is a recursive function that takes the distance from the
 * target position, and the current node in the list that we are iterating
 * through, and recurses until it reaches the target node.
 *
 * asymptotic analysis where base case is met: O(1)
 * asymptotic analysis where base case is not met: O(n)
 */
string SortedList::getElementRec(int nodesToPos, Node* curr) const {
	if (nodesToPos == 0) {
		// return value of target node
		return curr->value;
	}

	// recurse into next node
    return getElementRec(nodesToPos - 1, curr->next);
}

/* getLength() returns the length of the list.
 *
 * asymptotic analysis: O(1)
 */
int SortedList::getLength() const {
    return this->length;
}

/*
 * insert() takes a value and converts it to a node, inserting the node into
 * the list while maintaining sorted order (ascending).
 *
 * asymptotic analysis where list is empty or input value is minimum: O(1)
 * asymptotic analysis otherwise: O(n)
 */
void SortedList::insert(const string& elem) {
	if (head == nullptr) {

		// list is empty
		head = new Node(elem, nullptr);
		this->length++;
		return;

	} else if (head->value > elem) {

		// element to insert is smaller than the rest of the list
		head = new Node(elem, head);
		return;
	}

	// otherwise, iterate over list and insert in correct position
	insertRec(elem, head);
}

/*
 * insertRec() is a recursive function that takes the value to be inserted,
 * and the current node in the list we are iterating over. it recurses into the
 * next node until the correct position is found for the new node, maintaining
 * sorted order (ascending).
 *
 * asymptotic analysis where base case is met: O(1)
 * asymptotic analysis where base case is not met: O(n)
 */
void SortedList::insertRec(const string& elem, Node* curr) {
	if (curr->next == nullptr) {

		// end of list
		curr->next = new Node(elem, nullptr);
		this->length++;
		return;

	} else if (curr->next->value >= elem) {

		// next value is larger than value we are inserting, so correct
		// position has been found
		curr->next = new Node(elem, curr->next);
		this->length++;
		return;
	}

	// recurse into the next element
	insertRec(elem, curr->next);
}

/*
 * isEmpty() returns true if the length of the list is zero.
 *
 * asymptotic analysis: O(1)
 */
bool SortedList::isEmpty() const {
    return this->length == 0;
}

/*
 * remove() takes the position of a node and removes it from the list, updating
 * the length of the list.
 *
 * asymptotic analysis where position is invalid: O(1)
 * asymptotic analysis where position is 0: O(1)
 * asymptotic analysis otherwise: O(n)
 */
void SortedList::remove(int position) {
	if (position < 0 || position > this->length - 1) {
		throw string("remove() error: position out of bounds");
	}

	if (position == 0) {
		if (this->length == 1) {

			// empty the list
			delete head;
			head = nullptr;

		} else if (this->length > 1){

			// update links
			Node* newHead = head->next;
			delete head;
			head = newHead;
		}
		this->length--; // update length
		return;
	}

	removeRec(position, head);
}

/*
 * removeRec() takes the distance from the target position and the current node
 * in the list we are iterating through, and recurses into the next node until
 * the target position has been reached. then it deletes the target node and
 * updates links and length of the list.
 *
 * asymptotic analysis where base case is met: O(1)
 * asymptotic analysis where base case is not met: O(n)
 */
void SortedList::removeRec(int nodesToPos, Node* curr) {

	// delete the next node if position has been reached
	if (nodesToPos == 1) {
		Node* tmp = curr->next->next;
		delete curr->next;
		curr->next = tmp;
		this->length--;
		return;
	}

	// otherwise recurse into the next node
	removeRec(nodesToPos - 1, curr->next);
}

/*
 * replace() takes the position of the target node and a new string and
 * replaces the node's value with the new value.
 *
 * this is not used by the TUI, but it is useful for debugging purposes.
 *
 * asymptotic analysis where position is invalid: O(1)
 * asymptotic analysis otherwise: O(n)
 */
void SortedList::replace(int position, const string& elem) {
    if (position < 0 || position >= this->length) {
        throw string("replace: error, position out of bounds");
    }

    remove(position);
    insert(elem);
}

/*
 * toVector() converts the sorted list into a vector for parsing in the TUI.
 *
 * asymptotic analysis: O(n)
 */
vector<string> SortedList::toVector() {
	vector<string> vec; // new vector
	Node* curr = head;
	while (curr != nullptr) {
		vec.push_back(curr->value); // append each element to the vector
		curr = curr->next;
	}
	return vec;
}

/*
 * find() uses the binary search algorithm to indicate if a value is in the
 * list. if so, returns true.
 *
 * asymptotic analysis:
 * - best case: O(1)
 * - average: O(log(n))
 * - worst case: O(log(n))
 */
bool SortedList::find(string s) {
	return (binSearchRec(s, 0, length - 1));
}

/*
 * binSearchRec implements the binary search algorithm on the list recursively.
 *
 * asymptotic analysis when base case is met: O(1)
 * otherwise:
 * - best case: O(1)
 * - average: O(log(n))
 * - worst case: O(log(n))
 */
bool SortedList::binSearchRec(string s, int left, int right) {
	// base case: element not found
	if (left > right) {
		return false;
	}
	int middle = left + (right - left)/2;
	if (getElement(middle) > s) {
		right = middle - 1;
	} else if (getElement(middle) < s) {
		left = middle + 1;
	} else {
		return true;
	}
	return binSearchRec(s, left, right);
}

/*
 * overloaded stream insertion operator, for debugging purposes.
 *
 * asymptotic analysis: O(n)
 */
ostream& operator<<(ostream& outStream, const SortedList& myObj) {
    if (myObj.isEmpty()) {
        outStream << "List is empty, no elements to display.\n";
    }
    else {
        typename SortedList::Node* curr = myObj.head;
        while (curr != nullptr) {
            outStream << curr->value;
            if (curr->next != nullptr) {
                outStream << " --> ";
            }
            curr = curr->next;
        }
        outStream << endl;
    }

    return outStream;
}

