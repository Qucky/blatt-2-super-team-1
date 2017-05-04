SRC = ./src/
INC = ./include/
OUT = ./bin/out

output: WordTable Main
	g++ -Wall word_table.o Main.o -o $(OUT)

WordTable: $(SRC)word_table.cpp $(INC)word_table.hpp
	g++ -Wall -c $(SRC)word_table.cpp

Main: $(SRC)Main.cpp $(INC)word_table.hpp
	g++ -Wall -c $(SRC)Main.cpp

.PHONY: clean

clean: 
	rm -f *.o
	rm -f $(OUT)



