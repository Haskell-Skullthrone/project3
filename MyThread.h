#pragma once
#include<iostream>
using namespace std;
//holds properties of the threads
class Partition{	
protected:
	int beginAddress;
	int endAddress;
	bool hole;
	int processID;
public:
	Partition() {
		beginAddress = endAddress = processID -1;
		hole = 1;
	}
	Partition(const Partition&p) {
		beginAddress = p.beginAddress;
		endAddress = p.endAddress;
		hole = p.hole;
		processID = p.processID;
	}
	int getBeginAddress() {
		return beginAddress;
	}
	void setBeginAddress(int a) {
		beginAddress = a;
	}
	int getEndAddress() {
		return endAddress;
	}
	void setEndAddress(int a) {
		endAddress = a;
	}
	void setHole(bool h) {
		hole = h;
		processID = hole ? -1 : processID;
	}
	bool isHole() {
		return hole;
	}
	void setProcessId(int id) {
		processID = id;
		hole = id == -1;
	}
	int getProcessId() {
		return processID;
	}
	Partition(int _beginAddress, int _endAddress, bool _hole, int _processID) {
		beginAddress = _beginAddress;
		endAddress = _endAddress;
		hole = _hole;
		processID = _processID;
	}
	Partition(int _process):Partition(-1,-1,true,_process){}
	virtual ~Partition() {}
	friend bool operator==(Partition&p1,Partition&p2){
		return p1.getProcessId()==p2.getProcessId();
	}
	friend ostream&operator<<(ostream&s, Partition&p) {
		if (!p.isHole()) {
			s << "Process: " << p.getProcessId() << " Begin Address: "
				<< p.getBeginAddress() << " End address: " << p.getEndAddress()<<'\n';
		}
		return s;
	}
	Partition&operator=(Partition&p) {
		return Partition(p);
	}
};

