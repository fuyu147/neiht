#include <print>

#include "program/program.hpp"

int main()
{
        std::println("Hey there");

        // auto *program = new proj::program();
        //
        // program->run();

        auto files = proj::getFileFromDialog();

        for (auto file : files)
        {
                std::println("filepath: {}", file);
        }

        return 0;
}
