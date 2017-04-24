//============================================================================
// Name        : AlgDatII.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "word_table.hpp"
using namespace std;

int main() {
	WordTable word(3,29);
	cout << "before add: " << word << endl;
	word.add("foo",1);
	word.add("baa",2);
	word.add("baz",3);
	word.add("foo",5);
	cout << "after add: " << word << endl;
	WordTable::entry_ptr find = word.find("bazz");
	if(find) {
		cout << *find << endl;
	} else {
		cout << "not found" << endl;
	}

	return 0;
}
