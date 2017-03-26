#include <iostream>
#include "MyLinkedList.h"
#include "MyThread.h"
using namespace std;
/***************************************************
*Memory class holds a linked list of type Partition*
*as well as some helper methods for working with it*
****************************************************/
static class Memory {
private:
	LinkedList<Partition>elems;				//holds threads
	Memory() {};											
	const int SIZE = 128;					//total memory, in KB
public:
	//function to call the private constructor on the single instance of mem
	void init();							
	//function to create or resize partitions
	bool Allocate(int processID, int amount);
	//function to combine free memory into one continuous block
	void Coalesce();
	//function to terminate a process with a given ID
	bool Remove(int processID);
	void printFreeSpace();		//print to standard out the amount of free space
	friend ostream&operator<<(ostream&s, const Memory&mem);
};
ostream&operator<<(ostream&s, const Memory&m) {
	s << m.elems;
	return s;
}
Memory*mem;	


/*Uses the pointers given by the accessors of the 
linked list class to move all the partitions
with an associated thread to the beginning of the
list, and remove all the "holes"in the memory
*/

void Memory::Coalesce() {
	LinkedList<Partition> temp = elems;
	//loop iterates until the end of the linkedlist is reached
	while(temp.getNext() != nullptr) {
		if (temp.getData()->isHole()) {
			temp.removeAt(0);
		}
		else {
			//calculate the distance to "shift"
			int shift = temp.getNext()->getData()->getBeginAddress() - temp.getData()->getEndAddress();
			//adjust the beginning and ending addresses accordingly
			temp.getNext()->getData()->setBeginAddress(temp.getNext()->getData()->getBeginAddress() - shift);
			temp.getNext()->getData()->setEndAddress(temp.getNext()->getData()->getEndAddress() - shift);
		}
		temp = *temp.getNext();
	}
}


/*coalesces the list, and uses the difference between 
the last partition's end address and the capacity of the 
memory to calculate free memory and output it to cout
*/

void Memory::printFreeSpace() {
	if (elems.getNext() != nullptr) {

		//make a reference to the linked list, and iterate accross to the 
		//last element of the coalesced list
		LinkedList<Partition> temp = elems;
		Coalesce();
		while (temp.getNext() != nullptr) {
			temp = *temp.getNext();
		}
		cout << "Free memory:"<<
				(SIZE - temp.getData()->getEndAddress())<<"KB\n";
	}
}


//allows the private constructor to be called, if the Memory is not already 
//instatiated

void Memory::init() {
	if(mem==nullptr)mem = new Memory();
}

//if a partition with the associated ID exists, resize accordingly
//otherwise, create a partition, if the memory has the required free space

bool Memory::Allocate(int processID, int amount) {

	if (elems.getLast().getEndAddress() + amount >= SIZE)
		Coalesce();
	if (elems.getLast().getEndAddress() + amount >= SIZE)
		return false;
	//set the beginning address to the end address of the preious element
	Partition temp(elems.getLast().getEndAddress(), 
		elems.getLast().getEndAddress()+amount, true, processID);
	if (elems.indexOf(temp)==-1) {
		elems.append(new LinkedList<Partition>(Partition(temp)));
		return true;
	}
	else {
		(elems[elems.indexOf(processID)]->getData()->setEndAddress(elems[elems.indexOf(temp)]->getData()->getEndAddress() + amount));
		if (elems[elems.indexOf(processID)]->getData()->getEndAddress() > (elems[elems.indexOf(processID) + 1]->getData()->getBeginAddress())) {
			Coalesce();
		}
		else if (elems[elems.indexOf(processID)]->getData()->getEndAddress() <= elems[elems.indexOf(processID)]->getData()->getBeginAddress()) {
			Remove(processID);
		}
	}

	return true;
}
//uses the removeAt method of hte LinkedList class to remove from the memory
bool Memory::Remove(int processID){
	Partition temp(-1, -1, true, processID);
	if(elems.indexOf(temp)!=-1){
		elems.removeAt(elems.indexOf(temp));
		return true;
	}else return false;
}