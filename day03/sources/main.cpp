#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

std::vector<std::string> readFullFile(std::string name)
{
    std::string line;
    std::vector<std::string> fullFile;
    std::ifstream file(name);
    std::pair<std::pair<int, int>, std::pair<int, int>> full;

    if (file.is_open())
        while (std::getline(file, line)) {
            if (line == "")
                continue;
            full.first = line.substr

        }
    else {
        std::cerr << "Incorrect file name or file can't be opened" << std::endl;
        exit(84);
    }
    file.close();
    return fullFile;
}

int main(int ac, char **av)
{
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> allPairs;
}