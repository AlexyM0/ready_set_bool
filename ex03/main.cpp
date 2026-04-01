#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>

bool eval_formula(const std::string &formula)
{
    std::stack<bool> stck;
    for(char c : formula)
    {
        if (c == '1' || c == '0')
            stck.push(c == '1');
        else if (c == '!')
        {
            bool a = stck.top();
            stck.pop();
            stck.push(!a);
        }
        else
        {
            if (stck.size() < 2)
                throw std::runtime_error("invalid formula");
            bool b = stck.top();
            stck.pop();
            bool a = stck.top();
            stck.pop();

            if (c == '&') stck.push(a && b);
            else if (c == '|') stck.push(a || b);
            else if (c == '^') stck.push(a ^ b);
            else if (c == '>') stck.push(!a || b);
            else if (c == '=') stck.push(a == b);
            else
                throw std::runtime_error("invalid operator");
        }
    }
    if (stck.size() != 1)
        throw std::runtime_error("invalid formula: leftover values");
    return stck.top();
}

int main()
{
    try
    {
        std::cout << eval_formula("10&") << std::endl;   // false (0)
        std::cout << eval_formula("10|") << std::endl;   // true (1)
        std::cout << eval_formula("11>") << std::endl;   // true (1)
        std::cout << eval_formula("10=") << std::endl;   // false (0)
        std::cout << eval_formula("1011||=") << std::endl; // true (1)
    }
    catch(const char *msg)
    {
        std::cout << "Error: " << msg << std::endl;
    }
    

    return 0;
}