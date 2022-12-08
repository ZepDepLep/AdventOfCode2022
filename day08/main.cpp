#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <deque>

std::deque<std::string> readFullFile(std::string name)
{
    std::string line;
    std::deque<std::string> fullFile;
    std::ifstream file(name);

    if (file.is_open())
        while (std::getline(file, line)) {
            if (line == "")
                continue;
            fullFile.push_back(line);
        }
    else {
        std::cerr << "Incorrect file name or file can't be opened" << std::endl;
        exit(84);
    }
    file.close();
    return fullFile;
}

int checkTrees(int y, int x, std::deque<std::deque<int>> trees, std::pair<int, int> dir, int size)
{
    if (x < 0 || y < 0 || x > trees[y].size() - 1 || y > trees.size() - 1 || trees[y][x] >= size)
        return 1;
    else if (x == 0 || y == 0 || x == trees[y].size() - 1 || y == trees.size() - 1)
        return 1;
    else
        return 1 + checkTrees(y + dir.first, x + dir.second, trees, dir, size);
}

int main(int ac, char **av)
{
    std::deque<std::string> fullFile = readFullFile(av[1]);
    std::deque<std::deque<int>> trees;
    std::deque<int> lines;
    int visibleTrees = 0;
    int stockVisTree = 0;
    int treeSize = 0;

    for (auto line : fullFile) {
        for (auto ch : line) {
            lines.push_back(stoi(std::string(&ch)));
        }
        trees.push_back(lines);
        lines.clear();
    }
    for (size_t i = 0; i < trees.size(); ++i) {
        for (size_t g = 0; g < trees[i].size(); ++g) {
            treeSize = (checkTrees(i + 1, g, trees, std::make_pair(1, 0), trees[i][g]) * checkTrees(i, g + 1, trees, std::make_pair(0, 1), trees[i][g]) * checkTrees(i - 1, g, trees, std::make_pair(-1, 0), trees[i][g]) * checkTrees(i, g - 1, trees, std::make_pair(0, -1), trees[i][g]));
            if (treeSize > stockVisTree)
                stockVisTree = treeSize;
            else {
                std::cout << treeSize << std::endl;
            }
        }
    }
    std::cout << stockVisTree << std::endl;
}