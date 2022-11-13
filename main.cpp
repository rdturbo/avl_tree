#include "avl_tree.h"
#include "print_tree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void parseCommand(const std::vector<string> &parsed_input, AVLTree &tree)
{
    if (parsed_input[0] == "Insert")
    {
        std::cout << parsed_input[0] << " - " << parsed_input[1] << std::endl;
        tree.insert(stoi(parsed_input[1]));
    }
    else if (parsed_input[0] == "Delete")
    {
        std::cout << parsed_input[0] << " - " << parsed_input[1] << std::endl;
        tree.deleteNode(stoi(parsed_input[1]));
    }
    else if (parsed_input[0] == "Search")
    {
        if (parsed_input.size() > 2)
        {
            std::cout << parsed_input[0] << " - " << parsed_input[1] << " " << parsed_input[2] << std::endl;
            tree.search(stoi(parsed_input[1]), stoi(parsed_input[2]));
        }
        else
        {
            std::cout << parsed_input[0] << " - " << parsed_input[1] << std::endl;
            tree.search(stoi(parsed_input[1]));
        }
    }
}

std::vector<string> parseInput(const std::string &input)
{
    std::string temp = "";
    std::vector<string> store;
    for (char str : input)
    {
        if (str != '(')
        {
            if (str == ',' || str == ')')
            {
                store.push_back(temp);
                temp = "";
            }
            else
                temp += str;
        }
        else
        {
            store.push_back(temp);
            temp = "";
        }
    }
    return store;
}

void readFile(const std::string &file_name, AVLTree &tree)
{
    std::vector<string> command;
    std::ifstream file{file_name};

    std::string input;
    while (file >> input)
    {
        command = parseInput(input);
        if (command[0] == "Initialize")
        {
            tree.clearTree();
            std::cout << "----------------" << std::endl;
            std::cout << "Tree Initialized" << std::endl;
        }
        else
        {
            parseCommand(command, tree);
        }
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
    AVLTree tree;
    PrintTree p_tree;
    const std::string kFileName = args[1];
    readFile(kFileName, tree);
    p_tree.printTree(tree.root);
    tree.clearTree();
    // std::vector<std::string> results{"Initialize()", "Insert(21)"};
    // writeFile(results);

    // AVLTree tree;
    // PrintTree p_tree;
    // std::vector<int> inputs{14, 17, 11, 7, 53, 4, 13, 12, 8, 60, 19, 16, 20};

    // for (int val : inputs)
    // {
    //     tree.insert(val);
    // }

    // p_tree.printTree(tree.root);
    // tree.search(20);
    // tree.search(100);
    // tree.search(7);
    // tree.search(15, 80);
    // tree.search(100, 120);

    // std::vector<int> deletes{8, 7, 11, 14, 17};
    // for (int val : deletes)
    // {
    //     tree.deleteNode(val);
    //     p_tree.printTree(tree.root);
    // }
    // tree.clearTree();
    // std::cout << "" << std::endl;
    // for (std::string res : tree.result)
    // {
    //     std::cout << res << std::endl;
    // }

    return 0;
}