#ifndef BLOCK_HPP_
#define BLOCK_HPP_

#include <string>
#include <list>
#include <vector>

class Block {

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

	Block();
	~Block();
	bool add(std::string,long);
	entry_list_ptr entriesList();
	int & size();
	bool isEmpty();
	bool isFull();
	static const int BLOCK_CAPACITY = 2;
	friend std::ostream & operator <<(std::ostream&, const Block&);

	typedef Block* block_ptr;
	typedef std::list<block_ptr> block_list;
	typedef block_list* block_list_ptr;
	typedef std::vector<block_list_ptr> entry_hash;

private:

	entry_list::iterator findInList(entry_list_ptr,std::string);

	int mSize; /* Anzahl der Entries */
	entry_list_ptr mEntries;
};

#endif /* ifndef BLOCK_HPP_ */
