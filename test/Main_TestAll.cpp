#include <gtest/gtest.h>

#include "../src/block.cpp"
#include "../src/word_table.cpp"
#include "../src/words.cpp"

#include "block_test.cpp"
#include "block_entry_test.cpp"
#include "word_table_iterator_test.cpp"
#include "word_table_test.cpp"
#include "words_test.cpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
