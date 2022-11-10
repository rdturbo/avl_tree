#include "avl_tree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void readFile(const std::string &file_name)
{
    std::ifstream file{file_name};
    std::vector<std::string> commands;

    std::string input;
    while (file >> input)
    {
        commands.push_back(input);
    }

    for (std::string command : commands)
    {
        std::cout << command << std::endl;
    }
}

void writeFile(const std::vector<std::string> &output)
{
    std::ofstream file{"output.txt"};

    if (file.is_open())
    {
        std::cout << "Writing result to output.txt" << std::endl;
    }
    else
    {
        std::cerr << "Output.txt could not be opened..." << std::endl;
        return;
    }

    for (std::string res : output)
    {
        file << res << std::endl;
    }
}

int main(int n, char *args[])
{
    // const std::string kFileName = args[1];
    // readFile(kFileName);
    // std::vector<std::string> results{"Initialize()", "Insert(21)"};
    // writeFile(results);
    AVLTree tree;
    tree.insert(21);
    tree.insert(56);
    tree.insert(13);
    tree.print2D(tree.root, 5);
    tree.deleteNode(21);
    tree.deleteNode(56);
    tree.deleteNode(13);

    return 0;
}