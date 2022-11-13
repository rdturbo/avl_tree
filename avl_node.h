#ifndef AVL_NODE_H
#define AVL_NODE_H

class AVLNode
{
public:
    // Data Members
    int key{};               // key of the node
    int balance_factor{};    // balance factor of the node
    int height{};            // height of the node
    AVLNode *left{nullptr};  // pointer to left child
    AVLNode *right{nullptr}; // pointer to right child

    /**
     * Constructor for AVLNode
     *
     * @param key node key
     */
    AVLNode(int key);
};

#endif
