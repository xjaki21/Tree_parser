test/constructor: test/trie.o test/constructor.o
	g++ test/trie.o test/constructor.o -o test/constructor -std=c++17 -Wall

test/constructor.o: test/constructor.cpp test/trie.o
	g++ -c test/constructor.cpp -I include/ -o test/constructor.o -std=c++17 -Wall

test/trie.o: src/trie.cpp include/trie.hpp include/bag.hpp
	g++ -c src/trie.cpp -I include/ -o test/trie.o -std=c++17 -Wall


run: test/constructor
	./test/constructor
rm:
	rm -r test/*.o test/constructor 