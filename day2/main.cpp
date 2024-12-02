
#include <cstdio>
#include <vector>
#include "utils.hpp"

template <>
struct aoc::read_traits<std::vector<int>> final
{
    inline static auto read(FILE *file) -> std::vector<int>
    {
        std::vector<int> out;
        int cursor;

        do
        {
            fscanf(file, "%d", &cursor);
            out.push_back(cursor);
        } while (fgetc(file) == ' ');

        return out;
    }
};

int main()
{
    auto file = fopen("input.txt", "r");
    if (!file)
        aoc::fail("Couldn't find input file!");

    int safe_count{};
    int safe_rel_count{};

    auto is_safe = [](auto begin, auto end) -> bool
    {
        auto a = begin;
        auto b = a + 1;

        auto diff = *b - *a;
        int pos = int(diff > 0) - int(diff < 0);

        if (abs(diff) > 3)
            return false;

        while (++b != end)
        {
            ++a;
            diff = *b - *a;

            if (int(diff > 0) - int(diff < 0) != pos)
                return false; // different monotony
            if (abs(diff) > 3)
                return false; // out of bounds
        }

        return true;
    };

    auto is_safe_rel = [is_safe](auto begin, auto end) -> bool
    {
        for (auto iter = begin; iter != end; ++iter)
        {
            std::vector tmp(begin, iter);
            tmp.insert(tmp.end(), iter + 1, end);

            if (is_safe(tmp.begin(), tmp.end()))
                return true;
        }

        return false;
    };

    while (!feof(file))
    {
        std::vector<int> report = aoc::read(file);

        if (report.size() < 2)
            continue;

        auto begin = report.begin();
        auto end = report.end();

        auto safe = is_safe(begin, end);
        auto safe_rel = safe || is_safe_rel(begin, end);

        safe_count += safe;
        safe_rel_count += safe_rel;
    }

    printf("Safe reports: %d\n", safe_count);
    printf("Relaxed safe reports: %d\n", safe_rel_count);

    fclose(file);
}