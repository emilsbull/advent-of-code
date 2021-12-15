#ifndef MAP_UTILS_H
#define MAP_UTILS_H

#include <map>
#include <numeric>

namespace utils
{
    template <typename key, typename value>
    std::pair<key, value> mapMaxValue(std::map<key, value> map)
    {
        key retKey;
        value retVal = std::numeric_limits<value>::min();
        ;
        for (auto [mk, mv] : map)
        {
            if (mv > retVal)
            {
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
        for (auto [mk, mv] : map)
        {
            if (mv < retVal)
            {
                retVal = mv;
                retKey = mk;
            }
        }
        return {retKey, retVal};
    }
}
#endif // MAP_UTILS_H