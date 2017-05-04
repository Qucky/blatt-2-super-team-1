#include "gtest/gtest.h"

class WordTableIteratorTest : public ::testing::Test {
protected:
	virtual void SetUp() {}
	virtual void TearDown() {}
};

TEST(WordTableIteratorTest,EqualsTest) {
	WordTable word(3,29);
	word.add("foo",0);
	WordTable::Iterator want = word.begin();
	WordTable::Iterator have = word.begin();
	EXPECT_TRUE(want == have);
}

TEST(WordTableIteratorTest,NotEqualsTest) {
	WordTable word(3,29);
	word.add("foo",0);
	word.add("baa",0);
	WordTable::Iterator want = word.begin();
	++want;
	WordTable::Iterator have = word.begin();
	EXPECT_TRUE(want != have);
}

TEST(WordTableIteratorTest,AssignTest) {
	WordTable word(3,29);
	word.add("foo",0);
	word.add("baa",0);
	WordTable::Iterator want = word.begin();
	WordTable::Iterator have = word.begin();
	++want;
	have = want;
	EXPECT_TRUE(want == have);
}

TEST(WordTableIteratorTest,DerefTest) {
	WordTable word(3,29);
	word.add("foo",0);
	WordTable::Iterator want = word.begin();
	EXPECT_EQ("foo",(*want).value());
}

TEST(WordTableIteratorTest,PrefixIncrementTest) {
	WordTable word(3,29);
	word.add("foo",0);
	word.add("baa",0);
	WordTable::Iterator first = word.begin();
	WordTable::Iterator second = ++first;
	EXPECT_TRUE(first == second);
}

TEST(WordTableIteratorTest,PostfixIncrementTest) {
	WordTable word(3,29);
	word.add("foo",0);
	word.add("baa",0);
	WordTable::Iterator first = word.begin();
	WordTable::Iterator second = first++;
	EXPECT_FALSE(first == second);
}

