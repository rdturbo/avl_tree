avltree: main.o
	g++ main.o -o avltree

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o avltree output.txt
	