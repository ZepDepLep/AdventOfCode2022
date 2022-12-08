#include "directory.hpp"

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

int readingFile(std::deque<int> &sizes, std::deque<std::string> &file)
{
    int where = 0;
    static int filePos = 0;

    sizes.push_back(0);
    where = sizes.size() - 1;
    while (filePos < file.size()) {
        if (file[filePos][0] != '$' && file[filePos].find("dir") == file[filePos].npos) {
            try {
                sizes[where] += stoi(file[filePos].substr(0, file[filePos].find_first_of(' ')));
            } catch (std::invalid_argument) {
                exit(84);
            }
            ++filePos;
        } else if (file[filePos].find("cd") != file[filePos].npos && file[filePos].find("..") == file[filePos].npos) {
            ++filePos;
            sizes[where] += readingFile(sizes, file);
        } else if (file[filePos] == "$ cd ..")
            break;
        else
            ++filePos;
    }
    ++filePos;
    return sizes[where];
}

int main(int ac, char **av)
{
    std::deque<std::string> fullFile = readFullFile(av[1]);
    std::deque<int> sizes;
    int size = readingFile(sizes, fullFile);
    int test = size;

/*    std::deque<DIR> dirs;
    std::string cpy;
    int size = 0;

    for (auto line : fullFile) {
        if (line[0] != '$' && line.find("dir") == line.npos) {
            dirs[dirs.size() - 1].addSize(stoi(line.substr(0, line.find_first_of(' '))));
        } else if (line.find("cd") != line.npos && line.find("..") == line.npos) {
            dirs.push_back(DIR(line.substr(line.find_first_of(' ') + 2).substr(line.find_first_of(' ') + 1)));
        } else if (line.find("dir") != line.npos) {
            dirs[dirs.size() - 1].addDir(line.substr(line.find_first_of(' ') + 1));
        }
    }
    for (auto &dir : dirs) {
        //std::cout << dir.getSize() << std::endl;
        std::cout << dir.getName() << " directories :";
        for (auto names : dir.getDir()) {
            std::cout << " " << names;
        }
        std::cout << std::endl;
    }
    for (auto &dir : dirs)
        dir.update(dirs);*/
    std::cout << 30000000 + (size - 70000000) << " size to free" << std::endl;
    for (auto &siz : sizes) {
        //std::cout << siz << std::endl;
        if (siz < 30000000 + (size - 70000000))
            sizes.erase(std::find(sizes.begin(), sizes.end(), siz));
    }
    for (auto &siz : sizes)
        if (test > siz)
            test = siz;
    std::cout << test << std::endl;
}