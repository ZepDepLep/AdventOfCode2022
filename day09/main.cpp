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

bool checkTouching(std::pair<int, int> tailPos, std::pair<int, int> headPos)
{
    if (headPos == std::make_pair(tailPos.first, tailPos.second) || headPos == std::make_pair(tailPos.first - 1, tailPos.second) || headPos == std::make_pair(tailPos.first + 1, tailPos.second) || headPos == std::make_pair(tailPos.first, tailPos.second - 1) || headPos == std::make_pair(tailPos.first, tailPos.second + 1) || headPos == std::make_pair(tailPos.first - 1, tailPos.second - 1) || headPos == std::make_pair(tailPos.first + 1, tailPos.second + 1) || headPos == std::make_pair(tailPos.first - 1, tailPos.second + 1) || headPos == std::make_pair(tailPos.first + 1, tailPos.second - 1))
        return true;
    return false;
}

std::deque<std::pair<int, int>> findAllPos(std::deque<std::pair<int, int>> poss)
{
    std::pair<int, int> tailPos = std::make_pair(0, 0);
    std::deque<std::pair<int, int>> positions;

    positions.push_back(tailPos);
    for (auto headPos : poss) {
        if (!checkTouching(tailPos, headPos)) {
            //std::cout << "Before : " << "tailPos.x=" << tailPos.first << ", tailPos.y=" << tailPos.second << "  headPos.x=" << headPos.first << ", headPos.y=" << headPos.second << std::endl;
            tailPos.first += (headPos.first < tailPos.first ? -1 : headPos.first == tailPos.first ? 0 : 1);
            tailPos.second += (headPos.second < tailPos.second ? -1 : headPos.second == tailPos.second ? 0 : 1);
            positions.push_back(tailPos);
        }
    }
    return positions;
}

int main(int ac, char **av)
{
    std::deque<std::string> file = readFullFile(av[1]);
    std::deque<std::pair<char, int>> instrs;
    std::pair<char, int> instr;
    std::deque<std::pair<int, int>> positions;
    std::deque<std::pair<int, int>> lonePositions;
    std::pair<int, int> headPos;
    std::pair<int, int> tailPos;
    std::pair<int, int> dir;

    positions.push_back(std::make_pair(0, 0));
    for (auto line : file) {
        instr.first = line[0];
        instr.second = stoi(line.substr(line.find_first_of(" ") + 1));
        switch (instr.first) {
            case 'R':
                dir.first = 1;
                dir.second = 0;
                break;
            case 'L':
                dir.first = -1;
                dir.second = 0;
                break;
            case 'U':
                dir.first = 0;
                dir.second = 1;
                break;
            case 'D':
                dir.first = 0;
                dir.second = -1;
                break;
            default:
                break;
        }
        for (int i = 0; i < instr.second; ++i) {
            headPos.first += dir.first;
            headPos.second += dir.second;
            positions.push_back(headPos);
        }
    }
    for (int i = 0; i < 9; ++i)
        positions = findAllPos(positions);
    for (auto kj : positions) {
        if (lonePositions.empty() || std::find(lonePositions.begin(), lonePositions.end(), kj) == lonePositions.end())
            lonePositions.push_back(kj);
    }
    std::cout << lonePositions.size() << std::endl;
}