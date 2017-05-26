#include "gtest/gtest.h"

class BlockEntryTest : public ::testing::Test {
protected:
	virtual void SetUp() {}
	virtual void TearDown() {}
};

TEST(BlockEntryTest, ValueTest) {
	Block::Entry entry("foo");
	EXPECT_EQ("foo",entry.value());
}

TEST(BlockEntryTest, AddPositionTest) {
	Block::Entry entry("foo");
	EXPECT_EQ(0,entry.positions().size());
	entry.addPosition(42);
	EXPECT_EQ(1,entry.positions().size());
	EXPECT_EQ(42,*entry.positions().begin());
	entry.addPosition(50);
	EXPECT_EQ(2,entry.positions().size());
	EXPECT_EQ(42,*entry.positions().begin());
	EXPECT_EQ(50,*(++entry.positions().begin()));
}
