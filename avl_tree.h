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
    std::map<int, AVLNode *> nodes;
    AVLNode *root{nullptr};

    // default constructor
    AVLTree() = default;

    void insert(int data);
    AVLNode *insert(AVLNode *parent, AVLNode *child);

    void deleteNode(int data);
    AVLNode *deleteNode(AVLNode *parent, const int &data);
    void clearTree();
    int leftSubtreeMax(AVLNode *node);

    void search(int data);
    void search(int low, int high);

    void update(AVLNode *node);
    AVLNode *rebalance(AVLNode *node);

    // rotations
    AVLNode *llCase(AVLNode *node);
    AVLNode *lrCase(AVLNode *node);
    AVLNode *rrCase(AVLNode *node);
    AVLNode *rlCase(AVLNode *node);

private:
    bool search(AVLNode *node, const int &data);
    std::vector<int> search(AVLNode *node, const int &low, const int &high);
};

#endif