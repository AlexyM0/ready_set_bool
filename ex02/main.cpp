#include <iostream>
#include <cstdint>

uint32_t grey_code(uint32_t a)
{
   return a ^ (a >> 1);
}


int main()
{
    std::cout << "Tests de multiplier :" << std::endl;

    std::cout << grey_code(0) << std::endl;
    std::cout << grey_code(1) << std::endl;
    std::cout << grey_code(2) << std::endl;
    std::cout << grey_code(3) << std::endl;
    std::cout << grey_code(4) << std::endl;
    std::cout << grey_code(5) << std::endl;
    std::cout << grey_code(6) << std::endl;
    std::cout << grey_code(7) << std::endl;
    std::cout << grey_code(8) << std::endl;

    return 0;
}