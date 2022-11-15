#include "avl_node.h"
#include "avl_tree.h"
#include "utilities.h"
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <iterator>
#include <algorithm>

// AVLTree member functions

/**
 * This insert method creates a new AVLNode
 * with given value and calls the other insert
 * method for inserting at one of the leaves
 * of the tree
 */
void AVLTree::insert(int data)
{
    AVLNode *child_node = new AVLNode(data);
    nodes[data] = child_node;
    root = AVLTree::insert(root, child_node);
    std::cout << "Node " << data << " inserted" << std::endl;
    std::cout << "--------------------------" << std::endl;
}

/**
 * Recursive method to find the correct parent
 * of the inserted child node. Updates the height
 * and balance factor of nodes on the way up.
 * Rebalances tree and returns root of rebalanced tree.
 */
AVLNode *AVLTree::insert(AVLNode *parent, AVLNode *child)
{
    if (parent == nullptr)
        return child;

    if (parent->key > child->key)
    {
        parent->left = AVLTree::insert(parent->left, child);
    }
    else
    {
        parent->right = AVLTree::insert(parent->right, child);
    }

    // AVLTree::updateHeightAndBF(parent);
    // return AVLTree::rebalance(parent);
    return AVLTree::updateAndRebalance(parent);
}

/**
 * DeleteNode calls search to confirm node exists
 * and then calls the other deleteNode method
 * for deletion of node.
 */
void AVLTree::deleteNode(int data)
{
    if (!AVLTree::search(root, data))
    {
        std::cout << "Node " << data << " doesn't exist." << std::endl;
        std::cout << "--------------------------" << std::endl;
        return;
    }
    root = AVLTree::deleteNode(root, data);
    std::cout << "Deleted Node " << data << std::endl;
    std::cout << "--------------------------" << std::endl;
}

/**
 * Recursive method to find node to be deleted and then
 * remove the pointer to child and have a pointer from
 * grandparent to child.
 */
AVLNode *AVLTree::deleteNode(AVLNode *parent, const int &data)
{
    if (parent == nullptr)
        return nullptr;

    if (parent->key > data)
        parent->left = AVLTree::deleteNode(parent->left, data);
    else if (parent->key < data)
        parent->right = AVLTree::deleteNode(parent->right, data);
    else
    {
        AVLNode *child{nullptr};
        if (parent->left == nullptr)
        {
            child = parent->right;
            nodes.erase(parent->key);
            delete parent;
            return child;
        }
        else if (parent->right == nullptr)
        {
            child = parent->left;
            nodes.erase(parent->key);
            delete parent;
            return child;
        }
        else
        {
            int left_max{AVLTree::leftSubtreeMax(parent->left)};
            parent->key = left_max;
            parent->left = AVLTree::deleteNode(parent->left, left_max);
        }
    }

    // AVLTree::updateHeightAndBF(parent);
    // return AVLTree::rebalance(parent);
    return AVLTree::updateAndRebalance(parent);
}

/**
 * Returns the max value node in the left subtree
 * of given node parameter. Helper func for deleteNode.
 */
int AVLTree::leftSubtreeMax(AVLNode *node)
{
    AVLNode *curr{node};
    while (curr->right != nullptr)
    {
        curr = curr->right;
    }
    return curr->key;
}

/**
 * Updates the height and balance factor of node
 */
void AVLTree::updateHeightAndBF(AVLNode *node)
{
    int left_height = (node->left != nullptr) ? node->left->height : -1;
    int right_height = (node->right != nullptr) ? node->right->height : -1;

    node->height = 1 + std::max(left_height, right_height);
    node->balance_factor = left_height - right_height;
}

/**
 * Rebalances tree if balance factor of node
 * is +2 or -2. Calls one of the case methods
 * for rebalancing.
 */
AVLNode *AVLTree::rebalance(AVLNode *node)
{
    // left heavy
    if (node->balance_factor == 2)
    {
        if (node->left->balance_factor == -1)
            return AVLTree::lrCase(node);
        else
            return AVLTree::llCase(node);
    }
    // right heavy
    else if (node->balance_factor == -2)
    {
        if (node->right->balance_factor == 1)
            return AVLTree::rlCase(node);
        else
            return AVLTree::rrCase(node);
    }
    else
    {
        return node;
    }
}

/**
 * Combines update and rebalance
 */
AVLNode *AVLTree::updateAndRebalance(AVLNode *node)
{
    AVLTree::updateHeightAndBF(node);
    return AVLTree::rebalance(node);
}

/**
 * Searches for node with given value.
 */
void AVLTree::search(int data)
{
    std::cout << "Node found: ";
    if (AVLTree::search(root, data))
    {
        std::cout << std::to_string(data) << std::endl;
        Utilities::writeFile(std::to_string(data));
    }
    else
    {
        std::cout << "NULL" << std::endl;
        Utilities::writeFile("NULL");
    }
    std::cout << "--------------------------" << std::endl;
}

/**
 * Searches for nodes in a given range.
 */
void AVLTree::search(int low, int high)
{
    std::vector<int> nums{AVLTree::search(root, low, high)};
    std::sort(nums.begin(), nums.end());

    std::cout << "Nodes found: ";
    if (nums.empty())
    {
        std::cout << "NULL" << std::endl;
        Utilities::writeFile("NULL");
    }
    else
    {
        std::ostringstream num_string;
        std::copy(nums.begin(), nums.end() - 1, std::ostream_iterator<int>(num_string, ","));
        num_string << nums.back();
        std::cout << num_string.str() << std::endl;
        Utilities::writeFile(num_string.str());
    }
    std::cout << "--------------------------" << std::endl;
}

/**
 * Returns vector of nodes found in low <= node.key <= high.
 * Vector is empty if no node found.
 */
std::vector<int> AVLTree::search(AVLNode *node, const int &low, const int &high)
{
    std::vector<int> numbers;

    std::stack<AVLNode *> stack;
    stack.push(node);

    while (!stack.empty())
    {
        AVLNode *curr = stack.top();
        stack.pop();
        if (curr != nullptr)
        {
            if (curr->key >= low && curr->key <= high)
                numbers.push_back(curr->key);

            if (low < curr->key)
                stack.push(curr->left);

            if (high > curr->key)
                stack.push(curr->right);
        }
    }

    return numbers;
}

/**
 * Returns true if node with given value is found in tree
 * else returns false.
 */
bool AVLTree::search(AVLNode *node, const int &data)
{
    if (node == nullptr)
        return false;

    if (node->key == data)
        return true;

    bool left_subtree{AVLTree::search(node->left, data)};
    bool right_subtree{AVLTree::search(node->right, data)};

    return (left_subtree || right_subtree);
}

/**
 * Left-Left case
 */
AVLNode *AVLTree::llCase(AVLNode *node)
{
    AVLNode *parent{nullptr};
    parent = node->left;
    node->left = parent->right;
    parent->right = node;

    AVLTree::updateHeightAndBF(node);
    AVLTree::updateHeightAndBF(parent);
    return parent;
}

/**
 * Right-Right case
 */
AVLNode *AVLTree::rrCase(AVLNode *node)
{
    AVLNode *parent{nullptr};
    parent = node->right;
    node->right = parent->left;
    parent->left = node;

    AVLTree::updateHeightAndBF(node);
    AVLTree::updateHeightAndBF(parent);
    return parent;
}

/**
 * Left-Right case
 */
AVLNode *AVLTree::lrCase(AVLNode *node)
{
    node->left = AVLTree::rrCase(node->left);
    return AVLTree::llCase(node);
}

/**
 * Right-Left case
 */
AVLNode *AVLTree::rlCase(AVLNode *node)
{
    node->right = AVLTree::llCase(node->right);
    return AVLTree::rrCase(node);
}

/**
 * Deletes all nodes in tree to prevent
 * memory leak.
 */
void AVLTree::clearTree()
{
    if (root == nullptr)
    {
        return;
    }

    for (auto &node : nodes)
    {
        delete node.second;
        node.second = nullptr;
        std::cout << "Deleted Node " << node.first << std::endl;
    }
    nodes.clear();
    root = nullptr;
}
