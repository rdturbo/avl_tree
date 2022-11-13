#ifndef UTILITIES_H
#define UTILITIES_H

#include "avl_tree.h"
#include <string>
#include <vector>

namespace Utilities
{

    /**
     * Clears data from output file before new read
     */
    void clearFile();

    /**
     * Reads input file
     *
     * @param file_name name of input file
     * @param tree object of AVLTree Class
     */
    void readFile(const std::string &file_name, AVLTree &tree);

    /**
     * Writes result to output file
     *
     * @param output result of the search methods
     */
    void writeFile(const std::string &output);

    /**
     * Parses input line by line
     *
     * @param input the input on a given line in the file
     *
     * @returns given input split into a vector
     */
    std::vector<std::string> parseInput(const std::string &input);

    /**
     * Parses the command from the parsed input vector
     * eg: ["Search", "21", "25"]
     *
     * @param parsed_input parsed input split into a vector
     * @param tree object of AVLTree Class
     * @param initialized true if tree has been intialized else false
     */
    void parseCommand(const std::vector<std::string> &parsed_input, AVLTree &tree, bool initialized);

} // namespace Utilities

#endif