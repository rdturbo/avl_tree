avltree: main.o avl_node.o avl_tree.o
	g++ main.o avl_node.o avl_tree.o -o avltree

main.o: main.cpp
	g++ -c main.cpp

avl_node.o: avl_node.cpp
	g++ -c avl_node.cpp

avl_tree.o: avl_tree.cpp
	g++ -c avl_tree.cpp

clean:
	rm *.o avltree output.txt
	