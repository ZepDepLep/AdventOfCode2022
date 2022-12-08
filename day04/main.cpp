#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> readFullFile(std::string name)
{
    std::string line;
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> fullFile;
    std::ifstream file(name);
    std::pair<std::pair<int, int>, std::pair<int, int>> full;

    if (file.is_open())
        while (std::getline(file, line)) {
            if (line == "")
                continue;
            full.first.first = std::stoi(line.substr(0, line.find_first_of('-')));
            line.erase(0, line.find_first_of('-') + 1);
            full.first.second = std::stoi(line.substr(0, line.find_first_of(',')));
            line.erase(0, line.find_first_of(',') + 1);
            full.second.first = std::stoi(line.substr(0, line.find_first_of('-')));
            line.erase(0, line.find_first_of('-') + 1);
            full.second.second = std::stoi(line);
            fullFile.push_back(full);
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
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> allPairs = readFullFile(av[1]);
    int count = 0;

    for (auto c : allPairs) {
        if ((c.first.first <= c.second.first && c.first.second >= c.second.first) || (c.first.first <= c.second.second && c.first.second >= c.second.second) || (c.first.first >= c.second.first && c.first.first <= c.second.second) || (c.first.second >= c.second.first && c.first.second <= c.second.second))
            ++count;
    }
    std::cout << count << std::endl;
}