/*
 * LinkedList.hpp
 *
 *  Created on: Oct 7, 2022
 *      Author: angela
 */

#ifndef HOMEWORK_03_ANGELAAA_SRC_LINKEDLIST_HPP_
#define HOMEWORK_03_ANGELAAA_SRC_LINKEDLIST_HPP_

#include "adts.hpp"


void quicksort(vector<string>&, int, int);
void swap(vector<string>&, int, int);

class SortedList {
	protected:
        // represents an element in the linked list
        struct Node {
            string value;
            Node* next;

            Node(string v = "", Node* n = nullptr)
            : value(v), next(n) { }
        };

        // a pointer to the front of the list
        Node* head;
        int length;

    private:
        void copy(const SortedList&);
        void clearRec();
        void copyRec(Node*, Node*);
        string getElementRec(int, Node*) const;
        void insertRec(const string&, Node*);
        void removeRec(int, Node*);
        void replaceRec(int, const string&, Node*);
        void appendRec(Node*, Node*);
        void append(string);
        bool binSearchRec(string, int, int);

    public:
        SortedList();
        SortedList(const SortedList&);
        SortedList& operator=(const SortedList&);
        ~SortedList();
        void clear();
        string getElement(int) const;
        int getLength() const;
        void insert(const string&);
        bool isEmpty() const;
        void remove(int);
        void replace(int, const string&);
        vector<string> toVector();
        void populate(vector<string>&);
        bool find(string);

        friend ostream& operator<<(ostream&, const SortedList&);
};


#include "SortedList.cpp"


#endif /* HOMEWORK_03_ANGELAAA_SRC_LINKEDLIST_HPP_ */
