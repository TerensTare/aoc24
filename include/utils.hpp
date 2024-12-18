
#pragma once

#include <concepts>
#include <cstdio>
#include <cstdlib>
#include <string>

#define aoc_define_read(type, fmt)                           \
    template <>                                              \
    struct ::aoc::read_traits<type> final                    \
    {                                                        \
        inline static auto read(FILE *file) noexcept -> type \
        {                                                    \
            type value;                                      \
            fscanf(file, fmt, &value);                       \
            return value;                                    \
        }                                                    \
    }

namespace aoc
{
    template <typename... Args>
    [[noreturn]]
    inline int fail(char const *fmt, Args &&...args)
    {
        printf(fmt, (Args &&)args...);
        exit(1);
        return 1;
    }

    template <typename T>
    struct read_traits;

    template <std::integral T>
    struct read_traits<T> final
    {
    };

    struct read_type final
    {
        template <typename T>
        inline operator T() const noexcept
        {
            if constexpr (requires { { read_traits<T>::read(file) } -> std::convertible_to<T>; })
            {
                return read_traits<T>::read(file);
            }
            else
            {
                static_assert(
                    std::is_void_v<T>,
                    "Type cannot be read from a file!\n"
                    "Use aoc_define_read as a shortcut (eg. `aoc_define_read(int, \"%d\")`) or for more control specialize read_traits<T> for your type eg.:\n"
                    "\n"
                    "```cpp\n"
                    "template <>\n"
                    "struct aoc::read_traits<int> final\n"
                    "{\n"
                    "    static int read(FILE *file) noexcept\n"
                    "    {\n"
                    "        int value{};\n"
                    "        std::fscanf(file, \"%d\", &value);\n"
                    "        return value;\n"
                    "    }\n"
                    "};\n"
                    "```");
            }
        }

        FILE *file;
    };

    inline read_type read(FILE *file) noexcept { return {file}; }

    inline std::string read_file(char const *path) noexcept
    {
        auto file = fopen(path, "r");
        if (!path)
            fail("Cannot find file!");

        fseek(file, 0, SEEK_END);
        int len = ftell(file);
        fseek(file, 0, SEEK_SET);

        std::string buffer;
        buffer.resize(len);

        fread(buffer.data(), 1, len, file);
        fclose(file);

        return buffer;
    }
}