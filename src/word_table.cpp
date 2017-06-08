#include "../include/word_table.hpp"

#include <math.h>
#include <stdexcept>
#include <sstream>

WordTable::WordTable(int _letters)
	: mLetters(_letters) {
		mData = Block::entry_hash(mInitialBlockNumber);
		mLength = 0;
		mBlockAmount = 0;
		mDataLevel = 0;
		mStepPointer = 0;
}

WordTable::~WordTable(void) {
	for(Block::entry_hash::iterator current = mData.begin(); current != mData.end(); ++current) {
		Block::block_list_ptr blocks = *current;
		if(blocks) {
			for(Block::block_list::iterator block_it = blocks->begin(); block_it != blocks->end(); ++block_it) {
				Block::block_ptr block = *block_it;
				if(block) {
					Block::entry_list_ptr entries = block->entriesList();
					for(Block::entry_list::iterator entry_it = entries->begin(); entry_it != entries->end(); ++entry_it) {
						Block::entry_ptr entry = *entry_it;
						if(entry) {
							delete entry;
						}
					}
					delete block;
				}
			}
			delete blocks;
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
	int hashValue = hash(value);
	if(hashValue >= (int) mData.size())
		mData.resize(hashValue + 1, NULL);
	Block::block_list_ptr blocks = mData.at(hashValue);
	if(NULL == blocks) {
		mData[hashValue] = new Block::block_list();
		blocks = mData.at(hashValue);
	}
	Block::block_list::iterator block_it = blocks->begin();
	Block::block_ptr block = *block_it; 
	while(block_it != blocks->end() && !block->add(value, position)) {
		++block_it;
	}
	if(block_it == blocks->end()) {
		block = new Block();
		block->add(value, position);
		blocks->push_back(block);
		++mBlockAmount;
	}
	++mLength;
	checkSize();
}

WordTable::Iterator WordTable::begin(void) {
	return Iterator(mData);
}

WordTable::Iterator WordTable::end(void) {
	return Iterator();
}

/* wenn man weißt, das die Entry nicht in die blocks Liste steht. */
void WordTable::add(Block::block_list_ptr blocks, Block::entry_ptr entry) {
	if(NULL == blocks) {
		blocks = new Block::block_list();
	}
	Block::block_ptr block = blocks->back();
	if(block->isFull()) {
		block = new Block();
		blocks->push_back(block);
		++mBlockAmount;
	}
	block->entriesList()->push_back(entry);
	++block->size();
}

void WordTable::moveEntries(Block::block_list_ptr blocks) {
	for(Block::block_list::iterator block_it = blocks->begin(); block_it != blocks->end(); ++block_it) {
		Block::block_ptr block = *block_it;
		Block::block_ptr last_block = blocks->back();
		while(block != last_block && !block->isFull()) {
			Block::entry_list_ptr last_entries = last_block->entriesList();
			Block::entry_list::iterator entry_it = last_entries->begin();
			while(entry_it != last_entries->end() || !block->isFull()) {
				Block::entry_ptr entry = *entry_it;
				block->entriesList()->push_back(entry);
				entry_it = last_entries->erase(entry_it);
			}
			if(entry_it == last_entries->end()) {
				blocks->pop_back();
				last_block = blocks->back();
				--mBlockAmount;
			}
		}
	}
}

void WordTable::checkSize() {
	if(mLength / (Block::BLOCK_CAPACITY * mBlockAmount) > limitValue) {
		Block::block_list_ptr blocks = mData[mStepPointer];
		Block::block_list_ptr newBucket = new Block::block_list;
		mData.push_back(newBucket);
		if(NULL != blocks) {
			for(Block::block_list::iterator blocks_it = blocks->begin(); blocks_it != blocks->end(); ++blocks_it) {
				Block::block_ptr block = *blocks_it;
				for(Block::entry_list::iterator entries_it = block->entriesList()->begin(); entries_it != block->entriesList()->end(); ++entries_it) {
					Block::entry_ptr entry = *entries_it;
					int hashValue = hash2(entry->value());
					if(hashValue != mStepPointer) { // Erster Zahl ist eine 1, am Ende verschieben
						add(newBucket, entry);
					}
				}
			}
			moveEntries(blocks);
			if(mData[mStepPointer] == mData[mInitialBlockNumber * pow(2, mDataLevel)]) {
				mStepPointer = 0;
				++mDataLevel;
			} else {
				++mStepPointer;
			}
		}
	}
}

Block::entry_ptr WordTable::find(std::string value) {
	Block::entry_ptr result = 0;
	Block::block_list_ptr blocks = mData[hash(value)];
	if(blocks) {
		for(Block::block_list::iterator block_it = blocks->begin(); block_it != blocks->end() && 0 == result; ++block_it) {
			Block::entry_list_ptr entries = (*block_it)->entriesList();
			for(Block::entry_list::iterator entry_it = entries->begin(); entry_it != entries->end() && 0 == result; ++entry_it) {
				if((*entry_it)->value() == value) {
					result = *entry_it;
				}
			}
		}
	}
	return result;
}

int WordTable::size(void) {
	return mLength;
}

int WordTable::hash2(std::string & value) {
	int result = 0;
	int position = 0;
	for(std::string::iterator si1 = value.begin(); si1 != value.end(); ++si1) {
		result += *si1 * ++position;
	}
	return result % (mInitialBlockNumber * (int) pow(2, mDataLevel + 1));
}

int WordTable::hash1(std::string & value) {
	return hash2(value) % 2;
}

int WordTable::hash(std::string & value) {
	int hashValue = hash2(value);
	if (hashValue % 2 > mStepPointer)
		hashValue = hashValue % 2;
	return hashValue;
}

/*std::ostream & operator <<(std::ostream & out, WordTable & table) {
	out << "WordTable{ word_length => "
		<< table.mLetters
		<< ", size => "
		<< table.mLength;
	for(WordTable::Iterator it = table.begin(); it != table.end(); ++it){
		if(it != table.begin()) {
			out << ", ";
		} else {
			out << ", Blocks => {";
		}
		Block::block_list blocks = *it;
		for(Block::block_list::iterator block_it = blocks.begin(); block_it != blocks.end; ++block_it) {
			if(block_it != blocks.begin()) {
				out <<", ";
			}
			out << *it;
		}
	}
	if(table.mLength > 0) {
		out << "}";
	}
	out << "}";
	return out;
}*/

std::ostream & operator <<(std::ostream & out, WordTable & table) {
	out << "WordTable{ word_length => "
		<< table.mLetters
		<< ", size => "
		<< table.mLength;
	for(WordTable::Iterator it = table.begin(); it != table.end(); ++it){
		out << ", "
			<< *it;
	}
	if(table.mLength > 0) {
		out << "]";
	}
	out << "}";
	return out;
}

WordTable::Iterator::Iterator(void) {
	mCurrent = 0;
}

WordTable::Iterator::Iterator(Block::entry_hash & data) {
	if(0 == data.size()) {
		mCurrent = 0;
	} else {
		mDataIterator = data.begin();
		mDataIteratorEnd = data.end();
		slideNextData();
		if(mDataIterator == mDataIteratorEnd) {
			mCurrent = 0;
		} else {
			mBlocksIterator = (*mDataIterator) -> begin();
			mBlocksIteratorEnd = (*mDataIterator) -> end();
			mCurrent = *mBlocksIterator;
		}
	}
}

WordTable::Iterator::~Iterator(void) {}

Block WordTable::Iterator::operator *(void) {
	return *mCurrent;
}

void WordTable::Iterator::operator =(WordTable::Iterator other) {
	mDataIterator = other.mDataIterator;
	mDataIteratorEnd = other.mDataIteratorEnd;
	mBlocksIterator = other.mBlocksIterator;
	mBlocksIteratorEnd = other.mBlocksIteratorEnd;
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
		++mBlocksIterator;
		if(mBlocksIterator == mBlocksIteratorEnd) {
			slideNextData();
			if(mDataIterator == mDataIteratorEnd) {
				mCurrent = 0;
			} else {
				mBlocksIterator = (*mDataIterator) -> begin();
				mBlocksIteratorEnd = (*mDataIterator) -> end();
				mCurrent = *mBlocksIterator;
			}
		} else {
			mCurrent = *mBlocksIterator;
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
			Block::block_list_ptr target = *mDataIterator;
			while(NULL == target && mDataIterator != mDataIteratorEnd) {
				++mDataIterator;
				if(mDataIterator != mDataIteratorEnd) {
					target = *mDataIterator;
				}
			}
		}
	}
}
