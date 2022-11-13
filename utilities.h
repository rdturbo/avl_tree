#ifndef UTILITIES_H
#define UTILITIES_H

#include "avl_tree.h"
#include <string>
#include <vector>

namespace Utilities
{
    void clearFile();
    void readFile(const std::string &file_name, AVLTree &tree);
    void writeFile(const std::string &output);
    std::vector<std::string> parseInput(const std::string &input);
    void parseCommand(const std::vector<std::string> &parsed_input, AVLTree &tree, bool initialized);

} // namespace Utilities

#endif