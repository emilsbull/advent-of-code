#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <cstddef>

namespace utils
{
    template <typename C, typename FUN>
    void adiacentIndices(size_t row, size_t col, const C& container, FUN&& fun)
    {
        auto rowMax = container.size();
        auto colMax = container[row].size();

        if (row > 0) {
            if (col > 0) {
                // o|_|_
                // _|X|_
                // _|_|_
                fun(row - 1, col - 1);
            }
            // _|o|_
            // _|X|_
            // _|_|_
            fun(row - 1, col);
            if (col < colMax - 1) {
                // _|_|o
                // _|X|_
                // _|_|_
                fun(row - 1, col + 1);
            }
        }

        if (col > 0) {
            // _|_|_
            // o|X|_
            // _|_|_
            fun(row, col - 1);
        }

        if (col < colMax - 1) {
            // _|_|_
            // _|X|o
            // _|_|_
            fun(row, col + 1);
        }

        if (row < rowMax - 1) {
            if (col > 0) {
                // _|_|_
                // _|X|_
                // o|_|_
                fun(row + 1, col - 1);
            }
            // _|_|_
            // _|X|_
            // _|o|_
            fun(row + 1, col);
            if (col < colMax - 1) {
                // _|_|_
                // _|X|_
                // _|_|o
                fun(row + 1, col + 1);
            }
        }
    }

    template <typename C, typename FUN>
    void visitAdiacent(size_t row, size_t col, const C& container, FUN&& fun)
    {
        adiacentIndices(row, col, container, [&container, &fun](size_t r, size_t c) { fun(container[r][c]); });
    }
}  // namespace utils

#endif  // ARRAY_UTILS_H