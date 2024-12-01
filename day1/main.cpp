
#include <cinttypes>
#include <set>

#include "file.hpp"

int main()
{
    std::multiset<int> lhs, rhs;

    [&]
    {
        auto file = fopen("input.txt", "r");
        if (!file)
            aoc::fail("Cannot find input file!");

        int left, right;
        while (!feof(file))
        {
            char c;
            fscanf(file, "%d   %d%c", &left, &right, &c);

            lhs.insert(left);
            rhs.insert(right);
        }

        fclose(file);
    }();

    int dst = 0;
    for (auto right = rhs.begin(); auto const &left : lhs)
    {
        dst += abs(left - *right++);
    }

    printf("Distance: %d\n", dst);

    std::uint64_t score = 0;
    for (auto const &id : lhs)
    {
        score += id * rhs.count(id);
    }

    printf("Similarity score: %" PRIu64 "\n", score);
}