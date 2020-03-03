#pragma once

class StackElement
{
public:
	char data;
	StackElement* next;
};
class Stack
{
private:
	StackElement* top;
public:
	Stack();
	~Stack();
	bool empty() const;
	int peek() const;
	void push(int);
	int pop();
};
