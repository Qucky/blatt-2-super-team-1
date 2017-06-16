#include "block.h"

#include <iostream>
#include <sstream>

Block::Block() {
    mSize = 0;
    mEntries = new entry_list;
}

Block::~Block() {}

/* true falls die Entry in diesem Block eingefügt wurde */
bool Block::add(std::string value, long position) {
    entry_list_ptr entries = mEntries;
    //entry_list::iterator it = findInList(entries, value);
    entry_list::iterator it = findInList(value);
    entry_ptr entry;
    if(it == entries->end() && isFull())
        return false;
    if(it == entries->end()) {
        entry = new Entry(value);
        entries->push_back(entry);
    } else {
        entry = *it;
    }
    entry->addPosition(position);
    ++mSize;
    return true;
}

Block::entry_list::iterator Block::findInList(std::string value) {
    for(Block::entry_list::iterator current = mEntries -> begin(); current != mEntries -> end(); ++current) {
        entry_ptr ptr = *current;
        if(ptr -> value() == value) {
            return current;
        }
    }
    return mEntries -> end();
}

int & Block::size() {
    return mSize;
}

bool Block::isEmpty() {
    return (BLOCK_CAPACITY - mEntries->size() == 0);
}

bool Block::isFull() {
    return (BLOCK_CAPACITY == mEntries->size());
}

Block::entry_list_ptr Block::entriesList() {
    return mEntries;
}

/*Block::block_list::iterator findInList(block_list_ptr list, std::string value) {
    for(Block::block_list::iterator block_it = list->begin(); block_it != list->end(); ++block_it) {
        Block::block_ptr block = *block_it;
        for(Block::entry_list::iterator entry_it = block->entriesList()->begin(); entry_it != block->entriesList()->end(); ++entry_it) {
            Block::entry_ptr ptr = *entry_it;
            if(ptr->value() == value) {
                return entry_it;
            }
        }
    }
    return list->end();
}*/

std::ostream & operator <<(std::ostream & out, const Block & block) {
    out << std::endl
        << "[Block{ number of words => "
        << block.mSize;
    for(Block::entry_list::iterator it = block.mEntries->begin();
            it != block.mEntries->end();
            ++it) {
        if(it != block.mEntries->begin()) {
            out << ", ";
        } else {
            out << ", words => [";
        }
        out << **it;
    }
    if(block.mEntries->size() > 0) {
        out << "]";
    }
    out << "}";
    return out;
}

Block::Entry::Entry() {}

Block::Entry::Entry(std::string value) {
    mValue = value;
}

Block::Entry::~Entry(void) {}

std::string & Block::Entry::value(void) {
    return mValue;
}

void Block::Entry::addPosition(long position) {
    mPositions.push_back(position);
}

std::list<long> Block::Entry::positions(void) {
    return mPositions;
}

std::ostream & operator <<(std::ostream & out, const Block::Entry & entry) {
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
