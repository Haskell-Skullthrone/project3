#pragma once
#include<iostream>
using namespace std;
template<class dt>class LinkedList{
	protected:
	LinkedList*next;	//pointer to the next element of hte list
	dt*data;			//pointer to the data at this position of the list
	public:
	//swaps this element with the next element of the list
	void swap(){
		dt* a = new dt(*data);
		data=next->data;
		next->data=a;
	}
	//initializes both pointers to nullptr if the node is the last in the list
	LinkedList(){
		data = nullptr ;
		next = nullptr;
	}
	//initializer constructor
	LinkedList(dt _data){
		data=new dt(_data);
		next=new LinkedList<dt>();
	}
	//copy constructor
	LinkedList(const LinkedList<dt>& ll){
		if (&ll != nullptr) {
			next = ll.next;
			data = ll.data;
		}
	}	

	//deletes both pointers if the previous
	virtual~LinkedList(){
		if (next != nullptr) {
			delete data;
			delete next;
		}
	}
	
	//accessors and mutators for each pointer
	dt* getData(){
		return data;
	}
	LinkedList* getNext(){
		return next;
	}

	//uses recursion to iterate mutators accross  the list
	void insertAt(int index, dt _data){
		if(index == 0){
			LinkedList<dt>* temp = new LinkedList<dt>(_data);
			temp->next=next;
			next=temp;
			cout<<"inserting "<<_data<<'\n';
		}
		else{
			cout<<"iterating insertion"<<'\n';
			if(next!=nullptr)
				next->insertAt(index-1,_data);
			else
			next = new LinkedList<dt>(_data);
		}
	}
	void removeAt(int index){
		if(index==0){
			next=next->next;
		}
		else if(next!=nullptr){
			next->removeAt(index-1);
		}
	}
	int indexOf(dt _data, int index) {
		if (_data == *data)
			return index;
		else if (next->next != nullptr)
			return indexOf(_data, index + 1);
		else
			return -1;
	
	}
	int indexOf(dt _data) {
		return indexOf(_data, 0);
	}
	void append(LinkedList*ll) {
		if (next == nullptr)
			next = ll;
		else
			next->append(ll);
	}
	dt getLast() {
		if (next== nullptr)
			return *data;
		else return next->getLast();
	}
	friend ostream& operator<<(ostream&s,const LinkedList<dt>&l){
		s<<"data:"<<*(l.data)<<'\n';
		if((l.next->next)!=nullptr)
			s<<"iterating:"<<*(l.next)<<'\n';
		return s;
	}	
	LinkedList*operator[](int index) {
		if (index == 0)
			return this;
		else
			return &this[index-1];
	}
}; 