#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <sstream>
#include <game.h>

namespace utils {

inline std::ostream& operator<<(std::ostream &oStrStream, const Game::Tile &tile)
{
    oStrStream << (int)tile;
    return oStrStream;
}

template<typename T>
bool contain(std::vector<T> const &container, T value)
{
    return std::find(container.begin(), container.end(), value)
            != container.end();
}

template<typename T>
bool findAndRemove(std::vector<T> &container, T value)
{
    typename std::vector<T>::const_iterator it = std::find(container.begin(), container.end(), value);
    if (it != container.end()) {
        container.erase(it);
        return true;
    }
    return false;
}

template<typename T>
std::string join(std::vector<T> const &values, const std::string& separator = "")
{
    std::ostringstream result;
    typename std::vector<T>::const_iterator it = values.begin();
    typename std::vector<T>::const_iterator end = values.end();

    if (it != end) {
        result << *it;
        while (++it != end) {
            result << separator << *it;
        }
    }
    return result.str();
}

}

#endif // UTILS_H
