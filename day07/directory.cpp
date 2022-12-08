#include "directory.hpp"
#include <unistd.h>

DIR::DIR(std::string name)
{
    _name = name;
    _size = 0;
    _updated = false;
}
int DIR::getSize() const { return _size; }
std::string DIR::getName() const { return _name; }
void DIR::addSize(int size)
{
    _size += size;
}
std::deque<std::string> DIR::getDir() const { return _directories; }

void DIR::addDir(std::string directory)
{
    _directories.push_back(directory);
}
void DIR::update(std::deque<DIR> &dirs)
{
    if (_updated)
        return;
    std::cout << "IN " << _name << std::endl;
    for (auto &dir : dirs) {
        if (std::find(_directories.begin(), _directories.end(), dir.getName()) != _directories.end()) {
            if (!dir.getDir().empty()) {
                std::cout << "In for : " << _name << " asking " << dir.getName() << std::endl;
                sleep(1);
                dir.update(dirs);
            }
            _size += dir.getSize();
        }
    }
    _updated = true;
    std::cout << "OUT" << std::endl;
}