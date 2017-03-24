#pragma once
#include<iostream>
using namespace std;
template<class dt>class LinkedList{
	protected:
	LinkedList*next;
	dt*data;
	public:
	void swap(){
		dt* a = new dt(*data);
		data=next->data;
		next->data=a;
	}
	LinkedList(){
		data = NULL ;
		next = NULL;
	}
	LinkedList(dt _data){
		data=new dt(_data);
		next=new LinkedList<dt>();
	}
	LinkedList(const LinkedList<dt>& ll){
		next=ll.next;
		data=ll.data;
	}	


	virtual~LinkedList(){
		delete data;
		delete next;
	}
	
	dt getData(){
		return *data;
	}
	LinkedList* getNext(){
		return next;
	}
	void insertAt(int index, dt _data){
		if(index == 0){
			LinkedList<dt>* temp = new LinkedList<dt>(_data);
			temp->next=next;
			next=temp;
			cout<<"inserting "<<_data<<'\n';
		}
		else{
			cout<<"iterating insertion"<<'\n';
			if(next!=NULL)
				next->insertAt(index-1,_data);
			else
			next = new LinkedList<dt>(_data);
		}
	}
	void removeAt(int index){
		if(index==0){
			next=next->next;
		}
		else if(next!=NULL){
			next->removeAt(index-1);
		}
	}
	friend ostream& operator<<(ostream&s,const LinkedList<dt>&l){
		s<<"data:"<<*(l.data)<<'\n';
		if((l.next->next)!=NULL)
			s<<"iterating:"<<*(l.next)<<'\n';
		return s;
	}	
}; 