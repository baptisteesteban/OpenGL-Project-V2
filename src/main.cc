#include <iostream>
#include <camera.hh>

int main(void)
{
    Camera v({0, 0, 0}, {1, 0, 0}, {0, 1, 0});
    std::cout << v << "\n";
    return 0;
}