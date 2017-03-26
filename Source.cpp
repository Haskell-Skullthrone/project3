#include<iostream>			
#include "Source.h"
using namespace std;

int main() {
	while (!cin.eof()) {
		int a, b;
		cin >> a;
		switch(a) {
		case -1:
			mem->printFreeSpace();
			cin >>b;
			break;
		case 0:
			cout << *mem;
			cin >> b;
			break;
		default:
			cin >> b;
			if (b == 0)
				mem->Remove(b);
			else
				mem->Allocate(a, b);
		}

	}
	return 0;
}