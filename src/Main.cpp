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
	cout << w << endl;
	return 0;
}
