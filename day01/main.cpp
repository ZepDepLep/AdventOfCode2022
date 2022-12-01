#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

std::vector<int> getCalories(std::string name)
{
    std::string line;
    std::vector<int> elfCalories;
    std::ifstream file(name);
    size_t count = 0;

    if (file.is_open()) {
        elfCalories.push_back(0);
        while (std::getline(file, line)) {
            if (line == "") {
                elfCalories.push_back(0);
                ++count;
                continue;
            } else
                elfCalories[count] += std::stoi(line);
        }
    } else {
        std::cerr << "Incorrect file name or file can't be opened" << std::endl;
        exit(84);
    }
    file.close();
    return elfCalories;
}

int main(int ac, char **av)
{
    std::vector<int> calories = getCalories(av[1]);
    int max = 0;
    std::vector<int> topCalories;

    for (int i = 0; i < 3; ++i) {
        for (int elf : calories)
            if (max < elf)
                max = elf;
        calories.erase(std::find(calories.begin(), calories.end(), max));
        topCalories.push_back(max);
        max = 0;
    }
    std::cout << topCalories[0] + topCalories[1] + topCalories[2] << std::endl;
}