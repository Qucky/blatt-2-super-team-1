#ifndef WORD_TABLE_HPP_
#define WORD_TABLE_HPP_

#include <string>
#include <vector>
#include <list>

/**
 * Die Klasse word_table implementiert eine Hashtabelle über Wörter.
 *
 * Die Wörter haben alle die selbe Länge, und werden durch eine statische
 * Hashfunktion gespeichert.
 *
 * @author	mroeder
 * @date	10.04.2017
 */

class WordTable {

public:

    /** Es gibt für jedes Wort im Text eine Entry im Hashtabelle.
     *
     * Eine Entry enthält jeweils das Wort und alle seine Positionen im Text.
     */
    class Entry {
    public:
        /** Der Konstruktor ohne Parameter initialisiert keine Werte.*/
        Entry();
        /** Der Konstruktor wird das Parameter als Wort des Entry speichern.*/
        Entry(std::string);
        /** Der Destruktor macht nichts besonders.*/
        virtual ~Entry(void);
        /** @return Das Wort*/
        std::string & value();
        /** Fügt eine neue Position für das Wort hinzu.
         * @param position Die Stelle im Text*/
        void addPosition(long position);
        /** @return Liste den Positionen dieses Wortes*/
        std::list<long> positions(void);
        /** Gibt das Wort und seine Positionen auf.
         * @param out Output Stream
         * @param entry Entry für dieses Wort*/
        friend std::ostream & operator <<(std::ostream&,const Entry&);
    private:
        /** Die Zeichenkette, die das Wort repräsentiert.*/
        std::string mValue;
        /** Die Liste von Stellen des Wortes im Text.*/
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

    /** Die Hashfunktion.
     * Das ist die Summe von den ASCII-Werten der Zeichen potenziert, und */
    int hash(std::string&);
    entry_list::iterator findInList(entry_list_ptr,std::string);

};



#endif /* WORD_TABLE_HPP_ */
