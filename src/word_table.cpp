/*
 * word_table.cpp
 *
 *  Created on: 10.04.2017
 *      Author: mroeder
 */

#include "../include/word_table.hpp"

#include <math.h>
#include <iostream>
#include <stdexcept>
#include <sstream>

WordTable::WordTable(int _letters, int _charsetSize)
	: mLetters(_letters), mMaxSize(pow(_charsetSize,_letters) - 1) {
	mData = entry_hash(mMaxSize);
	mLength = 0;
}

WordTable::~WordTable(void) {
	for(entry_hash::iterator current = mData.begin(); current != mData.end(); ++current) {
		entry_list_ptr entries_ptr = *current;
		if(entries_ptr) {
			entry_list entries = *entries_ptr;
			for(entry_list::iterator entry_it = entries.begin(); entry_it != entries.end(); ++entry_it) {
				entry_ptr entry = *entry_it;
				if(entry) {
					delete entry;
				}
			}
			delete entries_ptr;
		}
	}
}

void WordTable::add(std::string value, long position) {
	if((unsigned int) mLetters != value.size()) {
		std::ostringstream stringStream;
		stringStream << "wrong word length <"
					 << value.size()
					 << "> for <"
					 << mLetters
					 << ">.";
		throw std::invalid_argument(stringStream.str());
	}
	entry_ptr entry;
	int hashValue = hash(value);
	entry_list_ptr entries = mData.at(hashValue);
	if(NULL == entries) {
		mData[hashValue] = new entry_list();
		entries = mData.at(hashValue);
	}
	entry_list::iterator it = findInList(entries,value);
	if(entries -> end() == it) {
		entry = new Entry(value);
		entries -> push_back(entry);
	} else {
		entry = *it;
	}
	entry->addPosition(position);
	++mLength;
}

WordTable::Iterator WordTable::begin(void) {
	return Iterator(mData);
}

WordTable::Iterator WordTable::end(void) {
	return Iterator();
}

WordTable::entry_ptr WordTable::find(std::string value) {
	entry_ptr result = 0;
	entry_list_ptr list = mData[hash(value)];
	if(list) {
		for(entry_list::iterator it = list -> begin(); it != list -> end() && 0 == result; ++it) {
			if((*it) -> value() == value) {
				result = *it;
			}
		}
	}
	return result;
}

int WordTable::size(void) {
	return mLength;
}

std::ostream & operator <<(std::ostream & out, WordTable & table) {
	out << "WordTable{ word_length => "
		<< table.mLetters
		<< ", size => "
		<< table.mLength;
	for(WordTable::Iterator it = table.begin(); it != table.end(); ++it){
		if(it != table.begin()) {
			out << ", ";
		} else {
			out << ", words => [";
		}
		out << *it;
	}
	if(table.mLength > 0) {
		out << "]";
	}
	out << "}";
	return out;
}

int WordTable::hash(std::string & value) {
	int result = 0;
	int position = 0;
	for(std::string::iterator si1 = value.begin(); si1 != value.end();++si1) {
		result += *si1 * ++position;
	}
	return result % mMaxSize;
}

WordTable::entry_list::iterator WordTable::findInList(WordTable::entry_list_ptr list, std::string value) {
	for(entry_list::iterator current = list -> begin(); current != list -> end(); ++current) {
		entry_ptr ptr = *current;
		if(ptr -> value() == value) {
			return current;
		}
	}
	return list -> end();
}

WordTable::Entry::Entry() {

}

WordTable::Entry::Entry(std::string value) {
	mValue = value;
}

WordTable::Entry::~Entry(void) {}

std::string & WordTable::Entry::value(void) {
	return mValue;
}

void WordTable::Entry::addPosition(long position) {
	mPositions.push_back(position);
}

std::list<long> WordTable::Entry::positions(void) {
	return mPositions;
}

std::ostream & operator <<(std::ostream & out, const WordTable::Entry & entry) {
	out 	<< "Entry{ value => '"
			<< entry.mValue
			<< "', positions => [";
	for(
			std::list<long int>::const_iterator it = entry.mPositions.begin();
			it != entry.mPositions.end();
			++it
	) {
		if(it != entry.mPositions.begin()) {
			out << ",";
		}
		out << *it;
	}
	out		<< "] }";
	return out;
}

WordTable::Iterator::Iterator(void) {
	mCurrent = 0;
}

WordTable::Iterator::Iterator(WordTable::entry_hash & data) {
	if(0 == data.size()) {
		mCurrent = 0;
	} else {
		mDataIterator = data.begin();
		mDataIteratorEnd = data.end();
		slideNextData();
		if(mDataIterator == mDataIteratorEnd) {
			mCurrent = 0;
		} else {
			mListIterator = (*mDataIterator) -> begin();
			mListIteratorEnd = (*mDataIterator) -> end();
			mCurrent = *mListIterator;
		}
	}
}

WordTable::Iterator::~Iterator(void) {}

WordTable::Entry WordTable::Iterator::operator *(void) {
	return *mCurrent;
}

void WordTable::Iterator::operator =(WordTable::Iterator other) {
	mDataIterator = other.mDataIterator;
	mDataIteratorEnd = other.mDataIteratorEnd;
	mListIterator = other.mListIterator;
	mListIteratorEnd = other.mListIteratorEnd;
	mCurrent = other.mCurrent;
}

bool WordTable::Iterator::operator ==(WordTable::Iterator other) {
	return other.mCurrent == mCurrent;
}

bool WordTable::Iterator::operator !=(WordTable::Iterator other) {
	return !(*this == other);
}

WordTable::Iterator & WordTable::Iterator::operator ++(void) {
	if(mCurrent) {
		++mListIterator;
		if(mListIterator == mListIteratorEnd) {
			slideNextData();
			if(mDataIterator == mDataIteratorEnd) {
				mCurrent = 0;
			} else {
				mListIterator = (*mDataIterator) -> begin();
				mListIteratorEnd = (*mDataIterator) -> end();
				mCurrent = *mListIterator;
			}
		} else {
			mCurrent = *mListIterator;
		}
	}
	return *this;
}

WordTable::Iterator WordTable::Iterator::operator ++(int dummy) {
	Iterator copy = *this;
	++(*this);
	return copy;
}

void WordTable::Iterator::slideNextData(void) {
	if(mDataIterator != mDataIteratorEnd) {
		mDataIterator++;
		if(mDataIterator != mDataIteratorEnd) {
			entry_list_ptr target = *mDataIterator;
			while(NULL == target && mDataIterator != mDataIteratorEnd) {
				++mDataIterator;
				if(mDataIterator != mDataIteratorEnd) {
					target = *mDataIterator;
				}
			}
		}
	}
}



