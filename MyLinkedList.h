#pragma once
#include<iostream>
using namespace std;
template<class dt>class LinkedList{
	protected:
	LinkedList*next;
	dt*data;
	public:
	void swap();
	LinkedList<dt>();
	LinkedList<dt>(dt _data);
	LinkedList<dt>(const LinkedList<dt>& ll);
	virtual~LinkedList();
		
	dt getData();
	LinkedList* getNext();
	void insertAt(int index, dt _data);
	void removeAt(int index);
	friend ostream& operator<<(ostream&s,const LinkedList<dt>&l);
}; 