//============================================================================
// Name        : AlgDatII.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "../include/word_table.hpp"
#include "../include/words.hpp"
using namespace std;

int main() {
	Words w(" foo 123! - > @  @@bar\n   baz\n");
	std::cout << "Taille du tableau: " << w.size() << std::endl;
	/* Problème : seul le premier bloc est affiché*/
	/*for(Words::Iterator it = w.begin(); it != w.end(); ++it) {
		cout << *it << endl;
	}*/
	cout << w << endl;
	return 0;
}
