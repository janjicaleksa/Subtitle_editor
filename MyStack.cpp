#include "MyStack.h"

MyStack::MyStack()
{
	this->top = new StackElem();
	this->top->str = "";
	this->top->next = nullptr;
}

MyStack::~MyStack()
{
	StackElem* tmp = this->top;
	while (this->top != nullptr) {
		this->top = this->top->next;
		delete tmp;
		tmp = this->top;
	}
}

void MyStack::setTop(string str)
{
	this->top = new StackElem();
	this->top->str = str;
	this->top->next = nullptr;
}

void MyStack::addToStack(string str)
{
	StackElem* add = new StackElem();
	add->str = str;
	if (this->top == nullptr) add->next = nullptr;
	else add->next = this->top;

	this->top = add;
}

void MyStack::removeTop()
{
	if (this->top == nullptr) return; 
	else {
		StackElem* tmp = this->top;
		this->top = this->top->next;
		delete tmp;
	}
	return;
}

string MyStack::getLastState()
{
	return this->top->str;
}
