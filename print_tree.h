#ifndef PRINT_TREE_H
#define PRINT_TREE_H
#include "avl_node.h"
#include <vector>
#include <string>

using namespace std;

class PrintTree
{
public:
    vector<vector<string>> printTree(AVLNode *root);

private:
    int maxDepth(AVLNode *node);
    void fillTable(AVLNode *node, int depth, int start, int end, vector<vector<string>> &table);
};

#endif