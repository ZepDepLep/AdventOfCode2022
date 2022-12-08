#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

std::vector<std::string> readFullFile(std::string name)
{
    std::string line;
    std::vector<std::string> fullFile;
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
    std::string list = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::vector<std::string> fullFile = readFullFile(av[1]);
    std::vector<std::pair<std::string, std::pair<std::string, std::string>>> divide;
    std::pair<std::string, std::pair<std::string, std::string>> slice;
    int score = 0;
    slice.first = "";
    slice.second.first = "";
    slice.second.second = "";

    for (std::string line : fullFile) {
        if (slice.first.empty())
            slice.first = line;
        else if (slice.second.first.empty())
            slice.second.first = line;
        else if (slice.second.second.empty())
            slice.second.second = line;
        if (!slice.first.empty() && !slice.second.first.empty() && !slice.second.second.empty()) {
            divide.push_back(slice);
            slice.first = "";
            slice.second.first = "";
            slice.second.second = "";
        }
    }
    for (auto line : divide) {
        for (int i = 0; i < list.size(); ++i) {
            if (line.first.find_first_of(list[i]) != line.first.npos && line.second.first.find_first_of(list[i]) != line.second.first.npos && line.second.second.find_first_of(list[i]) != line.second.second.npos) {
                std::cout << list[i] << std::endl;
                score += i + 1;
            }
        }
        std::cout << "hey" << std::endl;
    }
    std::cout << score << std::endl;
}