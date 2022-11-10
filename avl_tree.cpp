#include "avl_node.h"
#include "avl_tree.h"
#include <iostream>
#include <string>
#include <vector>

#define SPACE 10

// AVLTree member functions
void AVLTree::insert(int value)
{
    AVLNode *child_node = new AVLNode(value);
    nodes[value] = child_node;
    root = AVLTree::insert(root, child_node);
    std::cout << "Node " << value << " inserted" << std::endl;
}

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

    AVLTree::update(parent);
    return AVLTree::rebalance(parent);
}

void AVLTree::deleteNode(int value)
{
    delete nodes[value];
    nodes.erase(value);
}

void AVLTree::update(AVLNode *node)
{
    int left_height{};
    if (node->left == nullptr)
    {
        left_height = -1;
    }
    else
    {
        left_height = node->left->height;
    }

    int right_height{};
    if (node->right == nullptr)
    {
        right_height = -1;
    }
    else
    {
        right_height = node->right->height;
    }

    node->height = 1 + std::max(left_height, right_height);
    node->balance_factor = left_height - right_height;
}

AVLNode *AVLTree::rebalance(AVLNode *node)
{
    if (node->balance_factor == 2)
    {
        if (node->left->balance_factor > -1)
        {
            return AVLTree::llCase(node);
        }
        else
        {
            return AVLTree::lrCase(node);
        }
    }
    else if (node->balance_factor == -2)
    {
        if (node->right->balance_factor < 1)
        {
            return AVLTree::rrCase(node);
        }
        else
        {
            return AVLTree::rlCase(node);
        }
    }
    else
    {
        return node;
    }
}

AVLNode *AVLTree::llCase(AVLNode *node)
{
    AVLNode *parent{nullptr};
    parent = node->left;
    node->left = parent->right;
    parent->right = node;

    AVLTree::update(node);
    AVLTree::update(parent);
    return parent;
}

AVLNode *AVLTree::rrCase(AVLNode *node)
{
    AVLNode *parent{nullptr};
    parent = node->right;
    node->right = parent->left;
    parent->left = node;

    AVLTree::update(node);
    AVLTree::update(parent);
    return parent;
}

AVLNode *AVLTree::lrCase(AVLNode *node)
{
    node->left = AVLTree::rrCase(node->left);
    return AVLTree::llCase(node);
}

AVLNode *AVLTree::rlCase(AVLNode *node)
{
    node->right = AVLTree::llCase(node->right);
    return AVLTree::rrCase(node);
}

void AVLTree::print2D(AVLNode *r, int space)
{
    if (r == nullptr) // Base case  1
        return;
    space += SPACE;                    // Increase distance between levels   2
    AVLTree::print2D(r->right, space); // Process right child first 3
    std::cout << std::endl;
    for (int i = SPACE; i < space; i++) // 5
        std::cout << " ";               // 5.1
    std::cout << r->key << "\n";        // 6
    AVLTree::print2D(r->left, space);   // Process left child  7
}