#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <deque>

class DIR {
public:
    DIR(std::string name);
    ~DIR() = default;

    int getSize() const;
    std::string getName() const;
    void addSize(int size);
    void addDir(std::string directory);
    std::deque<std::string> getDir() const;
    void update(std::deque<DIR> &dirs);
private:
    std::string _name;
    int _size;
    std::deque<std::string> _directories;
    bool _updated;
};