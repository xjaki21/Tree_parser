test/main: test/trie.o test/main.o
	g++ test/trie.o test/main.o -o test/main -std=c++17 -Wall

test/main.o: test/main.cpp test/trie.o
	g++ -c test/main.cpp -I include/ -o test/main.o -std=c++17 -Wall

test/trie.o: src/trie.cpp include/trie.hpp include/bag.hpp
	g++ -c src/trie.cpp -I include/ -o test/trie.o -std=c++17 -Wall


run: test/main
	./test/main
rm:
	rm -r test/*.o test/main 

valgrind:
	valgrind --leak-check=full --track-origins=yes test/main
