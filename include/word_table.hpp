#ifndef WORD_TABLE_HPP_
#define WORD_TABLE_HPP_

#include "block.hpp"

class WordTable {

public:

	class Iterator {
	public:
		Iterator(void);
		Iterator(Block::entry_hash&);
		virtual ~Iterator(void);
		//Block::Entry operator *(void);
		Block operator *(void);
		void operator =(Iterator);
		bool operator ==(Iterator);
		bool operator !=(Iterator);
		Iterator & operator ++(void);
		Iterator operator ++(int);
	private:
		Block::entry_hash::iterator mDataIterator;
		Block::entry_hash::iterator mDataIteratorEnd;
		/*Block::entry_list::iterator mListIterator;
		Block::entry_list::iterator mListIteratorEnd;*/
		Block::block_list::iterator mBlocksIterator;
		Block::block_list::iterator mBlocksIteratorEnd;
		//Block::entry_ptr mCurrent;
		Block::block_ptr mCurrent;
		void slideNextData(void);
	};

	WordTable(int letters);
	virtual ~WordTable(void);
	void add(std::string,long);
	Iterator begin(void);
	Iterator end(void);
	Block::entry_ptr find(std::string);
	int size(void);
	friend std::ostream & operator <<(std::ostream&,WordTable&);

private:

	const int mLetters;
	Block::entry_hash mData;
	int mLength; /* Anzahl der Wörter */
	int mEntriesAmount;
	int mBlockAmount;
	int mDataLevel;
	static const int limitValue = 0.8;
	static const int mInitialBlockNumber = 1;
	int mStepPointer;

	int hash2(std::string&);
	int hash1(std::string&);
	int hash(std::string&);
	Block::block_list::iterator findInList(Block::block_list_ptr,std::string);

	void add(Block::block_list_ptr,Block::entry_ptr);
	void moveEntries(Block::block_list_ptr);
	void checkSize();

};

#endif /* WORD_TABLE_HPP_ */
