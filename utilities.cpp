#include "avl_tree.h"
#include "utilities.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void Utilities::clearFile()
{
    std::ofstream file{"output_file.txt"};
    file.clear();
}

void Utilities::readFile(const std::string &file_name, AVLTree &tree)
{
    Utilities::clearFile();
    std::vector<std::string> command;
    std::ifstream file{file_name};

    std::string input;
    while (file >> input)
    {
        command = Utilities::parseInput(input);
        if (command[0] == "Initialize")
        {
            tree.clearTree();
            std::cout << "----------------" << std::endl;
            std::cout << "Tree Initialized" << std::endl;
        }
        else
        {
            Utilities::parseCommand(command, tree);
        }
    }
    file.close();
}

void Utilities::writeFile(const std::string &output)
{
    std::ofstream file{"output_file.txt", std::ios::app};

    if (file.is_open())
    {
        std::cout << "Writing result to output.txt" << std::endl;
    }
    else
    {
        std::cerr << "Output.txt could not be opened..." << std::endl;
        return;
    }

    file << output << std::endl;
    file.close();
}

std::vector<std::string> Utilities::parseInput(const std::string &input)
{
    std::string temp = "";
    std::vector<std::string> store;
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

void Utilities::parseCommand(const std::vector<std::string> &parsed_input, AVLTree &tree)
{
    if (parsed_input[0] == "Insert")
    {
        std::cout << parsed_input[0] << " - " << parsed_input[1] << std::endl;
        tree.insert(std::stoi(parsed_input[1]));
    }
    else if (parsed_input[0] == "Delete")
    {
        std::cout << parsed_input[0] << " - " << parsed_input[1] << std::endl;
        tree.deleteNode(std::stoi(parsed_input[1]));
    }
    else if (parsed_input[0] == "Search")
    {
        if (parsed_input.size() > 2)
        {
            std::cout << parsed_input[0] << " - " << parsed_input[1] << " " << parsed_input[2] << std::endl;
            tree.search(std::stoi(parsed_input[1]), std::stoi(parsed_input[2]));
        }
        else
        {
            std::cout << parsed_input[0] << " - " << parsed_input[1] << std::endl;
            tree.search(std::stoi(parsed_input[1]));
        }
    }
}