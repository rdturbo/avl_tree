#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "avl_node.h"
#include <vector>
#include <string>
#include <map>

class AVLTree
{
public:
    // data members
    std::vector<std::string> result;
    std::map<int, AVLNode *> nodes;
    AVLNode *root{nullptr};

    // member functions
    AVLTree() = default;

    void insert(int value);
    AVLNode *insert(AVLNode *parent, AVLNode *child);

    void deleteNode(int val);

    void update(AVLNode *node);
    AVLNode *rebalance(AVLNode *node);

    // rotations
    AVLNode *llCase(AVLNode *node);
    AVLNode *lrCase(AVLNode *node);
    AVLNode *rrCase(AVLNode *node);
    AVLNode *rlCase(AVLNode *node);

    void print2D(AVLNode *r, int space);
};

#endif