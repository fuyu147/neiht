#include <print>

#include "program/program.hpp"

int main()
{
        std::println("Hey there");

        auto *program = new proj::program();

        program->run();

        return 0;
}
