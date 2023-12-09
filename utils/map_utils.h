#ifndef MAP_UTILS_H
#define MAP_UTILS_H

#include <map>
#include <vector>

#include <ostream>
#include <iostream>
#include <numeric>

namespace utils
{

    template <typename Key, typename Val>
    std::vector<std::pair<Key, Val> > sort(const std::map<Key, Val>& map)
    {
        std::vector<std::pair<Key, Val> > vec;

        for (auto& it : map) {
            vec.push_back(it);
        }
        sort(vec.begin(), vec.end(), [](std::pair<Key, Val>& a, std::pair<Key, Val>& b) { return a.first < b.first; });

        return vec;
    }

    template <typename Key, typename Val>
    std::ostream& operator<<(std::ostream& os, const std::pair<Key, Val>& p)
    {
        os << "(" << p.first << ":" << p.second << ")";
        return os;
    }

    template <typename Key, typename Val>
    void printMap(const std::map<Key, Val>& map)
    {
        auto v = sort(map);

        for (auto& e : v) {
            std::cout << e.first << " -> " << e.second << std::endl;
        }
    }

    template <typename key, typename value>
    std::pair<key, value> mapMaxValue(std::map<key, value> map)
    {
        key retKey;
        value retVal = std::numeric_limits<value>::min();
        ;
        for (auto [mk, mv] : map) {
            if (mv > retVal) {
                retVal = mv;
                retKey = mk;
            }
        }
        return {retKey, retVal};
    }

    template <typename key, typename value>
    std::pair<key, value> mapMinValue(std::map<key, value> map)
    {
        key retKey;
        value retVal = std::numeric_limits<value>::max();
        for (auto [mk, mv] : map) {
            if (mv < retVal) {
                retVal = mv;
                retKey = mk;
            }
        }
        return {retKey, retVal};
    }
}  // namespace utils
#endif  // MAP_UTILS_H