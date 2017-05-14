#ifndef WORDS_HPP_
#define WORDS_HPP_

#include <vector>
#include <list>
#include "block.hpp"
#include "word_table.hpp"

/**
 * Die Klasse Words ist verantwortlich für den Speichern und die Verwaltung der
 * Wörter.
 *
 * Eine Words-Klasse ist vorallem ein Vektor mit die Hashtabellen für alle
 * benötige Wortlänge, und die Methoden über diesen Vektor.
 *
 * @author	mroeder
 * @date 04.05.2017
 */

class Words {
public:

	typedef WordTable* table_ptr;
	typedef Block::entry_ptr entry_ptr;

	class Iterator {
	public:
		Iterator(void);
		Iterator(std::vector<table_ptr>&);
		virtual ~Iterator(void);
		Block operator *(void);
		void operator =(Iterator);
		bool operator ==(Iterator);
		bool operator !=(Iterator);
		Iterator & operator ++(void);
		Iterator operator ++(int);
	private:
		int mVectorIndex;
		WordTable::Iterator mInnerBegin;
		WordTable::Iterator mInnerEnd;
		std::vector<table_ptr> mData;
		void slideNext(void);
		void reset(void);
	};

	Words(std::string);
	virtual ~Words(void);
	entry_ptr find(std::string);
	int count(std::string);
	std::list<long> positions(std::string);
	Iterator begin(void);
	Iterator end(void);
	int size(void);

	static Words fromFile(std::string);
	static Words * newFromFile(std::string);
private:
	static const int LETTERS_COUNT = (26 * 2) + 10;
	std::vector<table_ptr> mTables;
	int mSize;
	std::string stripInput(std::string);
	std::list<std::string> splitInput(std::string);
	static std::string stringFromFile(std::string);
};




#endif /* WORDS_HPP_ */
