#include <list>
#include "gtest/gtest.h"

class WordTableTest : public ::testing::Test {
protected:
	virtual void SetUp() {}
	virtual void TearDown() {}
};

TEST(WordTable, SizeTest) {
	WordTable word(3,29);
	word.add("foo",0);
	EXPECT_EQ(1,word.size());
	word.add("foo",1);
	EXPECT_EQ(2,word.size());
}

TEST(WordTable, IterateTest) {
	WordTable word(3,29);
	word.add("foo",0);
	unsigned short int iteration_count = 0;
	for(WordTable::Iterator it = word.begin(); it != word.end(); ++it) {
		++iteration_count;
		WordTable::Entry entry = *it;
		EXPECT_EQ(entry.value(),"foo");
		std::list<long> positions = entry.positions();
		EXPECT_EQ(1,positions.size());
		EXPECT_EQ(0,positions.front());
	}
	EXPECT_EQ(1,iteration_count);
}

TEST(WordTable, AddTest) {
	WordTable word(3,29);
	word.add("foo",0);
	std::string want = "foo";
	std::string have = (*(word.begin())).value();
	EXPECT_EQ(want,have);
}

TEST(WordTable, FindTest) {
	WordTable word(3,29);
	word.add("foo",0);
	WordTable::entry_ptr ptr = word.find("foo");
	WordTable::entry_ptr ne = 0;
	EXPECT_NE(ne,ptr);
	EXPECT_EQ("foo",ptr -> value());
	ptr = word.find("baa");
	EXPECT_EQ(ne,ptr);
}
