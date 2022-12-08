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

int main(int ac, char **av)
{
    std::deque<std::string> fullFile = readFullFile(av[1]);
    std::deque<std::deque<char>> crates;
    std::deque<std::pair<int, std::pair<int, int>>> instructions;
    std::pair<int, std::pair<int, int>> instr;
    int g = 0;

    for (size_t i = 0; i < fullFile[0].size(); i += 3) {
        crates.push_back(std::deque<char>());
        ++i;
    }
    for (auto line : fullFile) {
        for (size_t i = 1, g = 0; i < line.size(); i += 3) {
            if (line[i] == ' ') {
                ++g;
                ++i;
                continue;
            }
            else if (isdigit(line[i])) {
                break;
            }
            crates[g].push_front(line[i]);
            ++g;
            ++i;
        }
        fullFile.erase(std::find(fullFile.begin(), fullFile.end(), line));
        if (isdigit(line[1])) {
            break;
        }
    }
    for (auto line : fullFile) {
        line.erase(0, line.find_first_of(" ") + 1);
        instr.first = stoi(line.substr(0, line.find_first_of(" ")));
        line.erase(0, line.find_first_of(" ") + 1);
        line.erase(0, line.find_first_of(" ") + 1);
        instr.second.first = stoi(line.substr(0, line.find_first_of(" ")));
        line.erase(0, line.find_first_of(" ") + 1);
        line.erase(0, line.find_first_of(" ") + 1);
        line.erase(0, line.find_first_of(" ") + 1);
        instr.second.second = stoi(line);
        instructions.push_back(instr);
    }
    for (auto inst : instructions) {
        for (int i = 0; i < inst.first; ++i) {
            crates[inst.second.second - 1].push_back(crates[inst.second.first - 1][crates[inst.second.first - 1].size() - (inst.first - i)]);
            crates[inst.second.first - 1].erase(crates[inst.second.first - 1].begin() + crates[inst.second.first - 1].size() - (inst.first - i));
        }
    }
    for (auto cr : crates) {
        for (auto c : cr) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
}