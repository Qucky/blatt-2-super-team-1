/*
 * words.cpp
 *
 *  Created on: 04.05.2017
 *      Author: mroeder
 */

#include <list>
#include <vector>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <streambuf>
#include "../include/words.hpp"

Words::Words(std::string in) {
	std::list<std::string> split = splitInput(stripInput(in));
	std::size_t last_pos = 0;
	mSize = 0;
	for(std::list<std::string>::iterator it = split.begin(); it != split.end();++it) {
		std::string word = *it;
		if(mTables.size() < word.size()+1) {
			mTables.resize(word.size() + 5);
		}
		if(0 == mTables[word.size()] ) {
			table_ptr table = new WordTable(word.size());
			mTables[word.size()] = table;
		}
		std::size_t pos = in.find(word,last_pos);
		mTables[word.size()] -> add(word,pos);
		++mSize;
		last_pos = pos + (word.size() == 1 ? 1 : word.size() - 1);
	}
}

Words::~Words(void) {}

Words::entry_ptr Words::find(std::string word) {
	entry_ptr result = 0;
	if(mTables.size() > word.size()) {
		table_ptr table = mTables[word.size()];
		if(table) {
			result = table->find(word);
		}
	}
	return result;
}

int Words::count(std::string word) {
	int result = 0;
	entry_ptr entry = find(word);
	if(entry) {
		result = entry -> positions().size();
	}
	return result;
}

std::list<long> Words::positions(std::string word) {
	std::list<long> result;
	entry_ptr entry = find(word);
	if(entry) {
		result = entry -> positions();
	}
	return result;
}

int Words::size(void) {
	return mSize;
}

std::vector<Words::table_ptr> Words::tables(void) {
	return mTables;
}

Words Words::fromFile(std::string path) {
	return Words(stringFromFile(path));
}

Words * Words::newFromFile(std::string path) {
	return new Words(stringFromFile(path));
}

std::string Words::stripInput(std::string in) {
	boost::trim(in);
	in.erase(std::remove_if(
		in.begin(),
		in.end(),
		[](char c) { return !std::iswblank(c) && !std::isalnum(c); }),
	in.end());
	return in;
}


std::list<std::string> Words::splitInput(std::string in) {
	std::list<std::string> result;
	size_t pos = 0;
	while ((pos = in.find(" ")) != std::string::npos) {
		std::string token = in.substr(0, pos);
		boost::trim(token);
		if("" != token && " " != token)
			result.push_back(token);
	    in.erase(0, pos + 1);
	}
	result.push_back(in);
	return result;
}

std::string Words::stringFromFile(std::string path) {
	std::ifstream t(path);
	std::string str;

	t.seekg(0, std::ios::end);
	str.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(t)),
				std::istreambuf_iterator<char>());
	return str;
}

/*std::ostream & operator <<(std::ostream & out, Words & w) {
	out << "Words{ number of words => "
		<< w.mSize;
	for(Words::Iterator it = w.begin(); it != w.end(); ++it) {
		out << "WordTable{ word_length => "
			<< std::endl
			<< *it;
	}
	out << "}";
	return out;
}*/

std::ostream & operator <<(std::ostream & out, Words & w) {
	out << "Words{ number of words => "
		<< w.mSize;
	for(std::vector<Words::table_ptr>::iterator it = w.mTables.begin(); it != w.mTables.end(); ++it)
	{
		if(*it != 0) {
			out << std::endl << **it;
		}
	}
	out << "}";
	return out;
}
