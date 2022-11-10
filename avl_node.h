#ifndef AVL_NODE_H
#define AVL_NODE_H

class AVLNode
{
public:
    // Data Members
    int key{};
    int balance_factor{};
    int height{};
    AVLNode *left{nullptr};
    AVLNode *right{nullptr};

    // Member Functions
    AVLNode(int value);
};

#endif
