#include "tab.hpp"
#include <fstream>
#include <string>

int proj::Tab::update()
{
        std::ifstream fstream(this->file);

        if (!fstream.is_open())
        {
                return 1;
        }

        this->lines = {};
        std::string buff;

        while (std::getline(fstream, buff))
        {
                this->lines.push_back(buff);
        }

        fstream.close();

        return 0;
}
