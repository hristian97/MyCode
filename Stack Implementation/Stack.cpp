#include<iostream>
#include "Stack.h"


Stack::Stack()
{
	top = NULL;
}
Stack::~Stack()
{
	StackElement *toDelete;
	while (top != NULL)
	{
		toDelete = top;
		top = top->next;
		delete toDelete;
	}
}
bool Stack::empty() const
{
	return top == NULL;
}
int Stack::peek() const {
	if (empty()) 
	{
		return 0;
	}

	return top->data;
}
void Stack::push(int x) {
	StackElement* p = new StackElement;
	p->data = x;
	p->next = top;
	top = p;
}
int Stack::pop() {
	if (empty()) {
		return 0;
	}
	StackElement* p = top;
	top = top->next;
	char x = p->data;
	delete p;
	return x;
}
