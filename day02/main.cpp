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
    std::vector<std::string> file = readFullFile(av[1]);
    int score = 0;

    for (auto string : file) {
        switch (string[0]) {
            case 'A':
                switch (string[2]) {
                    case 'X': score += 3; break;       //Pierre=1 feuille=2 ciseaux=3
                    case 'Y': score += 4; break;       //A=1 B=2 C=3
                    case 'Z': score += 8; break;       //win=6 tie=3 lose=0
                }
                break;
            case 'B':
                switch (string[2]) {
                    case 'X': score += 1; break;
                    case 'Y': score += 5; break;
                    case 'Z': score += 9; break;
                }
                break;
            case 'C':
                switch (string[2]) {
                    case 'X': score += 2; break;
                    case 'Y': score += 6; break;
                    case 'Z': score += 7; break;
                }
                break;
        }
    }
    std::cout << score << std::endl;
}