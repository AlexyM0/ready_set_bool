#include <iostream>
#include <cstdint>

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

uint32_t multiplier(uint32_t a, uint32_t b)
{
    uint32_t result = 0;

    while (b != 0)
    {
        if (b & 1)
            result = adder(result, a);

        a <<= 1;
        b >>= 1;
    }

    return result;
}

int main()
{
    std::cout << "Tests de multiplier :" << std::endl;

    std::cout << "1 * 1 = " << multiplier(1, 1) << std::endl;
    std::cout << "2 * 3 = " << multiplier(2, 3) << std::endl;
    std::cout << "5 * 3 = " << multiplier(5, 3) << std::endl;
    std::cout << "10 * 20 = " << multiplier(10, 20) << std::endl;
    std::cout << "0 * 7 = " << multiplier(0, 7) << std::endl;
    std::cout << "100 * 50 = " << multiplier(100, 50) << std::endl;

    return 0;
}