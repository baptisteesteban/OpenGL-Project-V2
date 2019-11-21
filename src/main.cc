#include <iostream>
#include "mat4f.hh"

int main(void)
{
    mat4f m = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    m.at(2, 2) = 4;
    std::cout << m << "\n";
    return 0;
}