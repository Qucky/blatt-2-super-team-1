#include "gtest/gtest.h"

class WordTableIteratorTest : public ::testing::Test {
protected:
	virtual void SetUp() {}
	virtual void TearDown() {}
};

TEST(WordTableIterator,Equals) {
	WordTable word(3,29);
	word.add("foo",0);
	WordTable::Iterator want = word.begin();
	WordTable::Iterator have = word.begin();
	EXPECT_TRUE(want == have);
}

TEST(WordTableIterator,NotEquals) {
	WordTable word(3,29);
	word.add("foo",0);
	word.add("baa",0);
	WordTable::Iterator want = word.begin();
	++want;
	WordTable::Iterator have = word.begin();
	EXPECT_TRUE(want != have);
}

TEST(WordTableIterator,Assign) {
	WordTable word(3,29);
	word.add("foo",0);
	word.add("baa",0);
	WordTable::Iterator want = word.begin();
	WordTable::Iterator have = word.begin();
	++want;
	have = want;
	EXPECT_TRUE(want == have);
}

TEST(WordTableIterator,Deref) {
	WordTable word(3,29);
	word.add("foo",0);
	WordTable::Iterator want = word.begin();
	EXPECT_EQ("foo",(*want).value());
}

TEST(WordTableIterator,PrefixIncrement) {
	WordTable word(3,29);
	word.add("foo",0);
	word.add("baa",0);
	WordTable::Iterator first = word.begin();
	WordTable::Iterator second = ++first;
	EXPECT_TRUE(first == second);
}

TEST(WordTableIterator,PostfixIncrement) {
	WordTable word(3,29);
	word.add("foo",0);
	word.add("baa",0);
	WordTable::Iterator first = word.begin();
	WordTable::Iterator second = first++;
	EXPECT_FALSE(first == second);
}

