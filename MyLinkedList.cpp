#include<iostream>
#include"MyLinkedList.h"
using namespace std;
template<class dt>LinkedList::void swap(){
	dt* a = new dt(*data);
	data=next->data;
	next->data=a;
}
	
template<class dt>LinkedList::LinkedList<dt>(){
	data = NULL ;
	next = NULL;
}
template<class dt>LinkedList::LinkedList<dt>(dt _data){
	data=new dt(_data);
	next=new LinkedList();
}
template<class dt>LinkedList::LinkedList<dt>(const LinkedList<dt>& ll){
	next=ll.next;
	data=ll.data;
}
LinkedList::virtual~LinkedList(){
	delete data;
	delete next;
}
	
template<class dt>LinkedList::dt getData(){
	return *data;
}
template<class dt>LinkedList::LinkedList* getNext(){
	return next;
}
template<class dt>LinkedList::void insertAt(int index, dt _data){
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
LinkedList::void removeAt(int index){
	if(index==0){
		next=next->next;
	}
	else if(next!=NULL){
		next->removeAt(index-1);
	}
}
template<class dt>ostream& operator<<(ostream&s,const LinkedList<dt>&l){
	s<<"data:"<<*(l.data)<<'\n';
	if((l.next->next)!=NULL)
		s<<"iterating:"<<*(l.next)<<'\n';
	return s;
}	
 		