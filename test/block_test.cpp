#include <list>
#include "gtest/gtest.h"

class BlockTest : public ::testing::Test {
protected:
	virtual void SetUp() {}
	virtual void TearDown() {}
};

TEST(BlockTest, SizeTest) {
	Block block;
	block.add("foo",0);
	EXPECT_EQ(1,block.size());
	block.add("foo",1);
	EXPECT_EQ(2,block.size());
}

TEST(BlockTest, IterateTest) {
	Block block;
	block.add("foo",0);
	unsigned short int iteration_count = 0;
	for(std::list<Block::entry_ptr>::iterator it = block.entriesList()->begin();
			it != block.entriesList()->end();
			++it) {
		++iteration_count;
		Block::Entry entry = **it;
		EXPECT_EQ(entry.value(),"foo");
		std::list<long> positions = entry.positions();
		EXPECT_EQ(1,positions.size());
		EXPECT_EQ(0,positions.front());
	}
	EXPECT_EQ(1,iteration_count);
}

TEST(BlockTest, AddTest) {
	Block block;
	block.add("foo",0);
	std::string want = "foo";
	std::string have = (*(block.entriesList()->begin()))->value();
	//std::string have = (*(word.begin())).value();
	EXPECT_EQ(want,have);
}
