#include "tab.hpp"
#include <fstream>
#include <string>

void proj::Tab::getLines()
{
  std::ifstream fstream(this->file);

  this->lines = {};
  if (fstream.is_open())
  {
    this->lines = {};
    std::string buff;

    while (std::getline(fstream, buff))
      this->lines.push_back(buff);

    fstream.close();
  }
}
