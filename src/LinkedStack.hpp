/*
 * LinkedStack.hpp
 *
 *  Created on: Oct 15, 2022
 *      Author: angela
 */

#ifndef HOMEWORK_04_A_SRC_LINKEDSTACK_HPP_
#define HOMEWORK_04_A_SRC_LINKEDSTACK_HPP_

#include "Stack.hpp"
#include "Square.hpp"

class LinkedStack : public Stack<Square> {
protected:
    // represents an element in the linked list
    struct Node {
		Square value;
		Node* next;
		Node* prev;

		Node(Square v = Square(), Node* n = nullptr, Node* p = nullptr)
		: value(v), next(n), prev(p) { }
    };

    // a pointer to the front of the list
    Node* head;

    // a pointer to the end of the list
	Node* last;
private:
    void copy(const LinkedStack&);
public:
    LinkedStack(const LinkedStack&);
    LinkedStack& operator=(const LinkedStack&);

    void save(string);

    void load(string);

    // remove all elements in the stack, resetting to the initial state
    virtual void clear() override;

    // return the current length of the stack
    virtual int getLength() const override;\

    // determine if the stack currently empty
    virtual bool isEmpty() const override;

    // return the element at the top of the stack
    virtual Square peek() const override;

    // remove the top element from the stack
    virtual void pop() override;

    // add the argument to the top of the stack
    virtual void push(const Square&) override;

    // rearranges the elements in the stack according to the argument
    virtual void rotate(typename Stack<Square>::Direction) override;

    LinkedStack();
	virtual ~LinkedStack();

	friend int main();
};

#include "LinkedStack.cpp"

#endif /* HOMEWORK_04_A_SRC_LINKEDSTACK_HPP_ */
