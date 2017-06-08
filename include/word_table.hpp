#ifndef WORD_TABLE_HPP_
#define WORD_TABLE_HPP_

#include "block.hpp"

/**
 * Die Klasse WordTable implementiert eine Hashtabelle über Wörter.
 *
 * Die Wörter haben alle die selbe Länge, und werden durch eine statische
 * Hashfunktion gespeichert.
 *
 * @author mroeder
 * @date 10.04.2017
 */

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

	/** Eine neues Array wird erzeugt.
	 * @param letters Länge den gespeicherten Wörter */
	WordTable(int letters);
	virtual ~WordTable(void);
	/** Fügt ein neues Wort hinzu.
	 * @param value Das Wort
	 * @param position Die Stelle */
	void add(std::string,long);
	Iterator begin(void);
	Iterator end(void);
	/** Sucht eine Wort über die Hashtabelle.
	 * @return Die Entry, wo das Wort gespeichert ist. */
	Block::entry_ptr find(std::string);
	/** @return mLength */
	int size(void);
	/** Methode zur Ausgabe der Tabelle. */
	friend std::ostream & operator <<(std::ostream&,WordTable&);

private:

	/** Länge den Wörter, die in diese Tabelle gespeichert sind. */
	const int mLetters;
	/** Die Tabelle. */
	Block::entry_hash mData;
	/** Anzahl von Wörter. */
	int mLength;
	/** Anzahl von Blöcke. */
	int mBlockAmount;
	int mDataLevel;
	static const int limitValue = 0.8;
	static const int mInitialBlockNumber = 1;
	int mStepPointer;

	int hash2(std::string&);
	int hash1(std::string&);
	/** Die Hashfunktion.
	 * Ruft die geeignete Methode, entweder hash2 oder hash1. */
	int hash(std::string&);
	// Block::block_list::iterator findInList(Block::block_list_ptr,std::string);

	/** Fügt eine Entry ein. Nützlich, um eine Entry zu verschieben. */
	void add(Block::block_list_ptr,Block::entry_ptr);
	/** Durch die Verschiebung von Entries erhält man Lücke in die Liste:
	 * andere Blöcke als der letzte sind nicht mehr voll. Diese Methode
	 * korrigiert das. */
	void moveEntries(Block::block_list_ptr);
	void checkSize();

};

#endif /* WORD_TABLE_HPP_ */
