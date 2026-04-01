#include <iostream>
#include <cstdint>

// & return 1 uniquement si les 2 bits valent 1
// ^ return 1 seulement quand les bits sont differents

uint32_t adder(uint32_t a, uint32_t b)
{
    while (b != 0)
    {
        uint32_t carry = a & b;
        a = a ^ b;
        b = carry << 1;
    }
    return a;
}

int main()
{
    std::cout << "Tests de adder :" << std::endl;

    std::cout << "1 + 1 = " << adder(1, 1) << std::endl;
    std::cout << "2 + 3 = " << adder(2, 3) << std::endl;
    std::cout << "5 + 3 = " << adder(5, 3) << std::endl;
    std::cout << "10 + 20 = " << adder(10, 20) << std::endl;
    std::cout << "0 + 7 = " << adder(0, 7) << std::endl;
    std::cout << "100 + 50 = " << adder(100, 50) << std::endl;

    return 0;
}