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
void AVLTree::insert(int value)
{

    AVLNode *child_node = new AVLNode(value);
    nodes[value] = child_node;
    root = AVLTree::insert(root, child_node);
    std::cout << "Node " << value << " inserted" << std::endl;
    std::cout << "--------------------------" << std::endl;
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

void AVLTree::deleteNode(int data)
{
    root = AVLTree::deleteNode(root, data);
    std::cout << "Deleted Node " << data << std::endl;
    std::cout << "--------------------------" << std::endl;
}

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

    AVLTree::update(parent);
    return AVLTree::rebalance(parent);
}

int AVLTree::leftSubtreeMax(AVLNode *node)
{
    AVLNode *curr{node};
    while (curr->right != nullptr)
    {
        curr = curr->right;
    }
    return curr->key;
}

void AVLTree::update(AVLNode *node)
{
    int left_height = (node->left != nullptr) ? node->left->height : -1;
    int right_height = (node->right != nullptr) ? node->right->height : -1;

    node->height = 1 + std::max(left_height, right_height);
    node->balance_factor = left_height - right_height;
}

AVLNode *AVLTree::rebalance(AVLNode *node)
{
    // left heavy
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
    // right heavy
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

void AVLTree::search(int data)
{
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
}

void AVLTree::search(int low, int high)
{
    std::vector<int> nums{AVLTree::search(root, low, high)};
    std::sort(nums.begin(), nums.end());
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
}

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
