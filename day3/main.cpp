
#include <string_view>

#include "utils.hpp"

int main()
{
    auto text = aoc::read_file("input.txt");

    bool enabled = true;

    int sum{};

    size_t index{};
    while ((index = text.find('(', index)) != std::string::npos)
    {
        if (strncmp("do", text.data() + (index - 2), 2) == 0)
        {
            enabled = true;
            index += 2;
        }
        else if (strncmp("don't", text.data() + (index - 5), 5) == 0)
        {
            enabled = false;
            index += 5;
        }
        else if (enabled && strncmp("mul", text.data() + (index - 3), 3) == 0)
        {
            ++index;

            sum += [&](char const *text)
            {
                int lhs{}, rhs{};
                for (int i{}; i < 3; ++i, ++index)
                {
                    if (isdigit(text[index]))
                        lhs = lhs * 10 + (text[index] - '0');
                    else if (text[index] == ',' && i > 0)
                        break;
                    else
                        return 0;
                }

                if (text[index++] != ',')
                    return 0;

                for (int i{}; i < 3; ++i, index++)
                {
                    if (isdigit(text[index]))
                        rhs = rhs * 10 + (text[index] - '0');
                    else if (text[index] == ')' && i > 0)
                        break;
                    else
                        return 0;
                }

                if (text[index++] != ')')
                    return 0;

                return lhs * rhs;
            }(text.data() + index);
        }
        else
            index++;
    }

    printf("Total sum is: %d\n", sum);
}