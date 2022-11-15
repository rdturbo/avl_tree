#include "avl_tree.h"
#include "utilities.h"
#include <iostream>
#include <string>

int main(int n, char *args[])
{
    AVLTree tree;
    const std::string kFileName = args[1];
    Utilities::readFile(kFileName, tree); // read file
    tree.clearTree(); // clear tree of all data (memory leak)
    return 0;
}