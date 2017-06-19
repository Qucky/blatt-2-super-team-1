#ifndef MOTS_HPP_
#define MOTS_HPP_

#include <vector>
#include <list>
#include "block.h"
#include "word_table.h"

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
    /**
     * Sucht nach einer geeigneten Hashtable und gibt als Ergebnis einen entry_ptr zurück falls
     * das gesuchte Wort gefunden wurde.
     * @brief find
     * @return entry_ptr eines Wortes.
     */
    entry_ptr find(std::string);
    /**
     * Gibt die Anzahl aller Vorkommen eines gesuchten Wortes im Text zurück.
     * @brief count
     * @return Anzahl Vorkommen des Wortes.
     */
    int count(std::string);
    /**
     * Gibt die genauen Positionen (offset) eines bestimmten Wortes im Text zurück.
     * @brief positions
     * @return Positionen aller Vorkommen.
     */
    std::list<long> positions(std::string);
    /**
     * Gibt die Anzahl der Wörter der gesamten Tabelle zurück.
     * @brief size
     * @return
     */
    int size(void);
    /**
     * List aller tables.
     * @brief tables
     * @return
     */
    std::vector<table_ptr> tables(void);

    /**
     * Gibt ein Word-Objekt zurück. Dieses Wort-Objekt wurde ein Text zum speichern übergeben.
     * @brief fromFile
     * @return Word-Objekt.
     */
    static Words fromFile(std::string);

    /**
     * Gibt ein neues Word-Objekt zurück. Dieses Wort-Objekt wurde ein Text zum speichern übergeben.
     * @brief fromFile
     * @return Neues Word-Objekt.
     */
    static Words * newFromFile(std::string);
    friend std::ostream & operator <<(std::ostream&,Words&);
private:
    /**
     * a-z, A-Z, 0-9
     * @brief LETTERS_COUNT
     */
    static const int LETTERS_COUNT = (26 * 2) + 10;
    /** Dieser Array enthält die entsprechende Hashtabellen für jede
     * Anzahl von Buchstaben */
    std::vector<table_ptr> mTables;
    /** Anzahl der Wörter in die gesamte Tabelle */
    int mSize;
    /**
     * Liest einen string und löscht alle Zeichen, die kein whitespace
     * oder eines der in LETTERS_COUNT beschriebenen Zeichen sind.
     *
     * @brief stripInput
     * @return Angepasster string.
     */
    std::string stripInput(std::string);
    /**
     * Trennt den eingegebenen string bei jedem whitespace.
     * @brief splitInput
     * @return Aufsplitteter string.
     */
    std::list<std::string> splitInput(std::string);

    /**
     * Liest einen string aus einer Datei.
     * @brief stringFromFile
     * @return
     */
    static std::string stringFromFile(std::string);
};




#endif /* WORDS_HPP_ */
