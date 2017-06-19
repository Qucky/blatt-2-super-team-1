#include "gtest/gtest.h"

class WordsTest : public ::testing::Test {
protected:
	virtual void SetUp() {}
	virtual void TearDown() {}
};

TEST(WordsTest, FindTest) {
	Words w("  foo  123! - > @  @@bar\n   baz\n");
	Words::entry_ptr have = w.find("foo");
	Words::entry_ptr not_want = 0;
	EXPECT_NE(not_want,have);
	EXPECT_EQ("foo",have -> value());
	EXPECT_EQ(2,*(have -> positions().begin()));
}

TEST(WordsTest, CountTest) {
	Words w("  foo  123! - > @  @@bar\n   baz\n");
	EXPECT_EQ(1,w.count("foo"));
}

TEST(WordsTest, PositionsTest) {
	Words w("  foo  123! - > @  @@bar\n   baz\n");
	EXPECT_EQ(2,*w.positions("foo").begin());
}

TEST(WordsTest, SizeTest) {
	Words w("  foo  123! - > @  @@bar\n   baz\n");
	EXPECT_EQ(4,w.size());
}

TEST(WordsTest, FromFileTest) {
	Words w = Words::fromFile("files/words.data_1.txt");
	EXPECT_EQ(4,w.size());
	EXPECT_EQ(1,w.count("foo"));
	EXPECT_EQ(1,w.count("bar"));
	EXPECT_EQ(1,w.count("baz"));
	EXPECT_EQ(1,w.count("123"));
}

TEST(WordsTest, NewFromFileTest) {
	Words * wp = Words::newFromFile("files/words.data_1.txt");
	Words w = *wp;
	EXPECT_EQ(4,w.size());
	EXPECT_EQ(1,w.count("foo"));
	EXPECT_EQ(1,w.count("bar"));
	EXPECT_EQ(1,w.count("baz"));
	EXPECT_EQ(1,w.count("123"));
	delete wp;
}
