#ifndef MOTS_HPP_
#define MOTS_HPP_

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

	Words(std::string);
	virtual ~Words(void);
	entry_ptr find(std::string);
	int count(std::string);
	std::list<long> positions(std::string);
	int size(void);
	std::vector<table_ptr> tables(void);

	static Words fromFile(std::string);
	static Words * newFromFile(std::string);
	friend std::ostream & operator <<(std::ostream&,Words&);
private:
	static const int LETTERS_COUNT = (26 * 2) + 10;
	/** Dieser Array enthält die entsprechende Hashtabellen für jede
	 * Anzahl von Buchstaben */
	std::vector<table_ptr> mTables;
	/** Anzahl der Wörter in die gesamte Tabelle */
	int mSize;
	std::string stripInput(std::string);
	std::list<std::string> splitInput(std::string);
	static std::string stringFromFile(std::string);
};




#endif /* WORDS_HPP_ */
