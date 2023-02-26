#ifndef MYSTACK_H
#define MYSTACK_H
#include <string>
using namespace std;

class MyStack {
public:
	MyStack();
	~MyStack();
	void setTop(string str);
	void addToStack(string str);
	void removeTop();
	string getLastState();
private:
	typedef struct stackElem {
		string str;
		struct stackElem* next;
	}StackElem;

	StackElem* top;
};

#endif 

