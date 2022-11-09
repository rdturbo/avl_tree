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

int main(int n, char *args[])
{
    const std::string kFileName = args[1];
    readFile(kFileName);

    return 0;
}