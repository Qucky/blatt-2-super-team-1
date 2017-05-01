/*
 * word_table.hpp
 *
 *  Created on: 10.04.2017
 *      Author: mroeder
 */

#ifndef WORD_TABLE_HPP_
#define WORD_TABLE_HPP_

#include <string>
#include <vector>
#include <list>


class WordTable {

public:

	class Entry {
	public:
		Entry();
		Entry(std::string);
		virtual ~Entry(void);
		std::string & value();
		void addPosition(long position);
		std::list<long> positions(void);
		friend std::ostream & operator <<(std::ostream&,const Entry&);
	private:
		std::string mValue;
		std::list<long> mPositions;
	};

	typedef Entry* entry_ptr;
	typedef std::list<entry_ptr> entry_list;
	typedef entry_list* entry_list_ptr;
	typedef std::vector<entry_list_ptr> entry_hash;

	class Iterator {
	public:
		Iterator(void);
		Iterator(entry_hash&);
		virtual ~Iterator(void);
		Entry operator *(void);
		void operator =(Iterator);
		bool operator ==(Iterator);
		bool operator !=(Iterator);
		Iterator & operator ++(void);
		Iterator operator ++(int);
	private:
		entry_hash::iterator mDataIterator;
		entry_hash::iterator mDataIteratorEnd;
		entry_list::iterator mListIterator;
		entry_list::iterator mListIteratorEnd;
		entry_ptr mCurrent;
		void slideNextData(void);
	};

	WordTable(int,int);
	virtual ~WordTable(void);
	void add(std::string,long);
	Iterator begin(void);
	Iterator end(void);
	entry_ptr find(std::string);
	int size(void);
	friend std::ostream & operator <<(std::ostream&,WordTable&);

private:

	const int mLetters;
	const int mMaxSize;
	entry_hash mData;
	int mLength;

	int hash(std::string&);
	entry_list::iterator findInList(entry_list_ptr,std::string);

};



#endif /* WORD_TABLE_HPP_ */
