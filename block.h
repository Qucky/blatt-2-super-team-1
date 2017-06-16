#ifndef BLOCK_HPP_
#define BLOCK_HPP_

#include <string>
#include <list>
#include <vector>

/**
 * Die Klasse Block implementiert die Blöcke, wo die Wörter gespeichert werden.
 *
 * In einem Block gibt es einen festen Anzahl von Wörter.
 *
 * @author Loïc Peyrot
 */

class Block {

public:

    /** Es gibt für jeden Wort im Text eine Entry in der Hashtabelle.
     *
     * Eine Entry enthält jeweils das Wort und alle seine Positionen im Text.
     */
    class Entry {
    public:
        /** Der Konstruktor ohne Parameter hat kein Effekt. */
        Entry();
        /** Der Konstruktor wird das Parameter als Wort des Entrys speichern.
         */
        Entry(std::string);
        /** Der Destruktor macht nichts besonders. */
        virtual ~Entry(void);
        /** @return Das Wort */
        std::string & value();
        /** Fügt eine neue Position für das Wort hinzu.
         * @param position Die Stelle im Text. */
        void addPosition(long position);
        /** @return Liste den Positionen dieses Wortes. */
        std::list<long> positions(void);
        /** Gibt das Wort und seien Positionen auf.
         * @param out Output Stream
         * @param entry Entry für dieses Wort */
        friend std::ostream & operator <<(std::ostream&,const Entry&);
    private:
        /** Die Zeichenkette, die das Wort repräsentiert. */
        std::string mValue;
        /** Die Liste von Stellen des Wortes im Text. */
        std::list<long> mPositions;
    };

    typedef Entry* entry_ptr;
    typedef std::list<entry_ptr> entry_list;
    typedef entry_list* entry_list_ptr;

    /** Setzt die Anzahl den Wörter auf 0 und erzeugt eine neue entry_list.*/
    Block();
    /** Der Destruktor macht nichts besonderes.*/
    ~Block();
    /** Fügt ein Wort und seine Stelle in dem Block hinzu.
     *
     * Falls der Block voll ist, gibt false zurück.
     * Falls das Wort schon darin ist, fügt nur die Stelle in die geeignete
     * Entry hinzu.
     * @return True falls die Entry eingefügt wurde, False sonst.
     * @param value Das Wort.
     * @param position Die Stelle. */
    bool add(std::string,long);
    /** @return this->mEntries */
    entry_list_ptr entriesList();
    /** @return this->mSize */
    int & size();
    /** @return True falls der Block leer ist. */
    bool isEmpty();
    /** @return True falls der Block voll ist. */
    bool isFull();
    /** Ṁaximale Anzahl an Entries. */
    static const int BLOCK_CAPACITY = 2;
    /** Methode zur Ausgabe von dem Block. */
    friend std::ostream & operator <<(std::ostream&, const Block&);

    typedef Block* block_ptr;
    typedef std::list<block_ptr> block_list;
    typedef block_list* block_list_ptr;
    typedef std::vector<block_list_ptr> entry_hash;

private:

    /** @return Iterator, der zeigt wo die Entry in der Liste steht.
     * @param value Gewünschtes Wort. */
    //entry_list::iterator findInList(entry_list_ptr,std::string);
    entry_list::iterator findInList(std::string);

    /** Anzahl der Entries. */
    int mSize;
    /** Pointer nach die Liste der Entries. */
    entry_list_ptr mEntries;
};

#endif /* ifndef BLOCK_HPP_ */
