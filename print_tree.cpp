#include "print_tree.h"
#include "avl_node.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

vector<vector<string>> PrintTree::printTree(AVLNode *root)
{

    vector<vector<string>> res;

    //
    // create table of empty strings ""
    // based on the tree height/width
    //
    int depth = PrintTree::maxDepth(root);
    int width = pow(2, depth + 1) - 1;
    vector<string> row(width, "--");
    for (int i = 0; i <= depth; i++)
    {
        res.push_back(row);
    }

    //
    // traverse the tree and fill in table values for non-NULL nodes
    //
    PrintTree::fillTable(root, 0, 0, width - 1, res);

    for (auto i : res)
    {
        for (auto j : i)
        {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << "-----------------------------------------------------------" << endl;
    return res;
}

int PrintTree::maxDepth(AVLNode *node)
{
    if (!node)
    {
        return -1;
    }

    int leftDepth = -1;
    if (node->left)
    {
        leftDepth = PrintTree::maxDepth(node->left);
    }

    int rightDepth = -1;
    if (node->right)
    {
        rightDepth = PrintTree::maxDepth(node->right);
    }

    return 1 + max(leftDepth, rightDepth);
}

void PrintTree::fillTable(AVLNode *node, int depth, int start, int end, vector<vector<string>> &table)
{
    if (!node)
    {
        return;
    }

    int mid = (int)(start + end) / 2;
    table[depth][mid] = to_string(node->key);

    if (node->left)
    {
        PrintTree::fillTable(node->left, depth + 1, start, mid - 1, table);
    }
    if (node->right)
    {
        PrintTree::fillTable(node->right, depth + 1, mid + 1, end, table);
    }
}
