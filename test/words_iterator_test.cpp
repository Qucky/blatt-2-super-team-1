#include "gtest/gtest.h"

class WordsIteratorTest : public ::testing::Test {
protected:
	virtual void SetUp() {}
	virtual void TearDown() {}
};

TEST(WordsIteratorTest,EqualsTest) {
	Words w("  foo  123! - > @  @@bar\n   baz\n");
	Words::Iterator first = w.begin();
	Words::Iterator second = w.begin();
	EXPECT_TRUE(first == second);
}

TEST(WordsIteratorTest,NotEqualsTest) {
	Words w("  foo  123! - > @  @@bar\n   baz\n");
	Words::Iterator first = w.begin();
	++first;
	Words::Iterator second = w.begin();
	EXPECT_TRUE(first != second);
}

TEST(WordsIteratorTest,AssignTest) {
	Words w("  foo  123! - > @  @@bar\n   baz\n");
	Words::Iterator first = w.begin();
	Words::Iterator second = w.begin();
	++first;
	second = first;
	EXPECT_TRUE(first == second);
}

TEST(WordsIteratorTest,DerefTest) {
	Words w("  foo  123! - > @  @@bar\n   baz\n");
	Words::Iterator first = w.begin();
	EXPECT_EQ("123",(*first).value());
}

TEST(WordsIteratorTest,PrefixIncrementTest) {
	Words w("  foo  123! - > @  @@bar\n   baz\n");
	Words::Iterator first = w.begin();
	Words::Iterator second = ++first;
	EXPECT_TRUE(first == second);
}

TEST(WordsIteratorTest,PostfixIncrementTest) {
	Words w("  foo  123! - > @  @@bar\n   baz\n");
	Words::Iterator first = w.begin();
	Words::Iterator second = first++;
	EXPECT_FALSE(first == second);
}
