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

int main(int ac, char** av) {
    std::deque<char> finding;
    std::string file = readFullFile(av[1])[0];
    int where = -1;

    std::cout << file.size() << std::endl;
    for (size_t i = 0; where == -1 && i < file.size() - 13; ++i) {
        finding.push_back(file[i]);
        for (std::size_t g = i + 1; g < i + 14; ++g)
            if (std::find(finding.begin(), finding.end(), file[g]) == finding.end())
                finding.push_back(file[g]);
        if (finding.size() == 14)
            where = i + 14;
        else {
            finding.clear();
        }
    }
    for (auto c : finding) {
        std::cout << c;
    }
    std::cout << std::endl;
    std::cout << where << std::endl;
}