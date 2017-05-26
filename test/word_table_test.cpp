#include "gtest/gtest.h"

class WordTableTest : public ::testing::Test {
protected:
	virtual void SetUp() {}
	virtual void TearDown() {}
};

TEST(WordTableTest, SizeTest) {
	WordTable word(3);
	word.add("foo",0);
	EXPECT_EQ(1,word.size());
	word.add("foo",1);
	EXPECT_EQ(2,word.size());
}

TEST(WordTableTest, FindTest) {
	WordTable word(3);
	word.add("foo",0);
	Block::entry_ptr ptr = word.find("foo");
	Block::entry_ptr ne = 0;
	EXPECT_NE(ne,ptr);
	EXPECT_EQ("foo",ptr -> value());
	ptr = word.find("baa");
	EXPECT_EQ(ne,ptr);
}
