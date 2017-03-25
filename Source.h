#include <iostream>
#include "MyLinkedList.h"
#include "MyThread.h"
class Memory {
private:
	LinkedList<Partition>elems;
	Memory() {};
	Memory(Partition*p, int amount, int hole);
	const int SIZE = 128;
public:
	void init();
	bool Allocate(int processID, int amount);
	void Coalesce();
	bool Remove(int processID);
	friend ostream&operator<<(ostream&s, const Memory&mem);
};
ostream&operator<<(ostream&s, const Memory&m) {
	s << m.elems;
	return s;
}
Memory*mem;
void Memory::Coalesce() {
	LinkedList<Partition> temp = elems;
	while(temp.getNext() != NULL) {
		int shift = temp.getNext()->getData()->getBeginAddress() - temp.getData()->getEndAddress();
		temp.getNext()->getData()->setBeginAddress(temp.getNext()->getData()->getBeginAddress() - shift);
		temp.getNext()->getData()->setEndAddress(temp.getNext()->getData()->getEndAddress() - shift);
	}
}
void Memory::init() {
	mem = new Memory();
}
bool Memory::Allocate(int processID, int amount) {

	if (elems.getLast().getEndAddress() + amount >= SIZE)
		Coalesce();
	if (elems.getLast().getEndAddress() + amount >= SIZE)
		return false;
	Partition temp(NULL, NULL, true, processID);
	if (elems.indexOf(temp)==-1) {
		elems.append(new LinkedList<Partition>(Partition(temp)));
		return true;
	}
	else (elems[elems.indexOf(temp)].getData()->setEndAddress(elems[elems.indexOf(temp)].getData()->getEndAddress() + amount));
		return true;
}
bool Memory::Remove(int processID){
	Partition temp(NULL,NULL,true,processID);
	if(elems.indexOf(temp)!=-1){
		elems.removeAt(elems.indexOf(processID));
		return true;
	}else return false;
}