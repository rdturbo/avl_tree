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
    std::map<int, AVLNode *> nodes; // map of all node val to node pointer
    AVLNode *root{nullptr};         // pointer to root of tree

    // default constructor
    AVLTree() = default;

    /**
     * Public method for inserting node into the tree.
     *
     * @param data the value of the node being inserted
     */
    void insert(int data);

    /**
     * Public method for deleting node from the tree.
     *
     * @param data the value of the node being deleted
     */
    void deleteNode(int data);

    /**
     * Public method for deleting all nodes from the tree.
     * For memory leak purposes.
     */
    void clearTree();

    /**
     * Public method for searching node in the tree.
     *
     * @param data the value of the node being searched
     */
    void search(int data);

    /**
     * Public method for searching nodes within a range
     * of values in the tree.
     *
     * @param low the lower limit
     * @param high the upper limit
     */
    void search(int low, int high);

private:
    /**
     * Inserts node as the child of a leaf
     *
     * @param parent pointer to the parent node
     * @param child pointer to the child node. (node being inserted)
     *
     * @returns pointer to root node after rebalance
     */
    AVLNode *insert(AVLNode *parent, AVLNode *child);

    /**
     * Seaches for a particular node starting from root
     *
     * @param node pointer to the node where search op is being performed
     * @param data value for the node being searched
     *
     * @returns true if node is found else false
     */
    bool search(AVLNode *node, const int &data);

    /**
     * Seaches for nodes within given range
     *
     * @param node pointer to the node where search op is being performed
     * @param low the lower limit
     * @param high the upper limit
     *
     * @returns vector of node values (can be empty)
     */
    std::vector<int> search(AVLNode *node, const int &low, const int &high);

    /**
     * Deletes node from the tree
     *
     * @param parent pointer to the parent node
     * @param data value for the node being deleted
     *
     * @returns pointer to root node after rebalance
     */
    AVLNode *deleteNode(AVLNode *parent, const int &data);

    /**
     * Finds node with max value in the left subtree
     *
     * @param node pointer to the node from where search op starts
     *
     * @returns max value node's key
     */
    int leftSubtreeMax(AVLNode *node);

    /**
     * Updates height and balance factor of node
     *
     * @param node pointer to the node whose
     * height and balance factor is being updated
     */
    void update(AVLNode *node);

    /**
     * Rebalances tree according to AVL tree definition
     *
     * @param node pointer to the node being rebalanced
     *
     * @returns pointer to root node after rebalance
     */
    AVLNode *rebalance(AVLNode *node);

    /**
     * The Left-Left Rotation Case
     *
     * @param node pointer to the node being rotated
     *
     * @returns pointer to root node of rotated subtree
     */
    AVLNode *llCase(AVLNode *node);

    /**
     * The Left-Right Rotation Case
     *
     * @param node pointer to the node being rotated
     *
     * @returns pointer to root node of rotated subtree
     */
    AVLNode *lrCase(AVLNode *node);

    /**
     * The Right-Right Rotation Case
     *
     * @param node pointer to the node being rotated
     *
     * @returns pointer to root node of rotated subtree
     */
    AVLNode *rrCase(AVLNode *node);

    /**
     * The Right-Left Rotation Case
     *
     * @param node pointer to the node being rotated
     *
     * @returns pointer to root node of rotated subtree
     */
    AVLNode *rlCase(AVLNode *node);
};

#endif