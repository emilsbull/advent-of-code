#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <vector>

namespace utils
{
    const char *ws = " \t\n\r\f\v";

    // trim from end of string (right)
    inline std::string &rtrim(std::string &s, const char *t = ws)
    {
        s.erase(s.find_last_not_of(t) + 1);
        return s;
    }

    // trim from beginning of string (left)
    inline std::string &ltrim(std::string &s, const char *t = ws)
    {
        s.erase(0, s.find_first_not_of(t));
        return s;
    }

    // trim from both ends of string (right then left)
    inline std::string &trim(std::string &s, const char *t = ws)
    {
        return ltrim(rtrim(s, t), t);
    }

    std::vector<std::string> splitString(std::string input, std::string delimiter)
    {
        std::vector<std::string> result;

        auto start = 0U;
        auto end = input.find(delimiter);
        while (end != std::string::npos)
        {
            auto substr = input.substr(start, end - start);
            trim(substr);
            if (substr.size() > 0)
            {
                result.push_back(substr);
            }
            start = end + delimiter.length();
            end = input.find(delimiter, start);
        }
        auto substr = input.substr(start, end - start);
        trim(substr);
        if (substr.size() > 0)
        {
            result.push_back(substr);
        }
        return result;
    }
}

#endif // STRING_UTILS_H