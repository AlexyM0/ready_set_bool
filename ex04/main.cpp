#include <iostream>
#include <stack>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stdexcept>

static std::vector<char> get_vars(const std::string &f)
{
    std::set<char> unique_vars;

    for (char c : f)
    {
        if (c >= 'A' && c <= 'Z')
        {
             unique_vars.insert(c);
        }
    }
    
    return std::vector<char>(unique_vars.begin(), unique_vars.end());
}

static bool eval(const std::string &f, std::map<char, bool> &v)
{
    std::stack<bool> st;
    for (char c : f)
    {
        if (c >= 'A' && c <= 'Z')
        {
            st.push(v[c]);
        }
        else if (c == '!')
        {
            if (st.empty())
                throw std::runtime_error("invalid formula");
            bool a = st.top(); st.pop();
            st.push(!a);
        }
        else
        {
            if (st.size() < 2)
                throw std::runtime_error("invalid formula");
            bool b = st.top(); st.pop();
            bool a = st.top(); st.pop();

            if (c == '&') st.push(a && b);
            else if (c == '|') st.push(a || b);
            else if (c == '^') st.push(a ^ b);
            else if (c == '>') st.push(!a || b);
            else if (c == '=') st.push(a == b);
            else
                throw std::runtime_error(std::string("invalid operator: ") + c);
        }
    }
    if (st.size() != 1)
        throw std::runtime_error("invalid formula: leftover values");
    return st.top();
}

void print_truth_table(const std::string &formula)
{
    std::vector<char> vars = get_vars(formula);
    int n = vars.size();
    int rows = 1 << n;

    std::cout << " ";
    for (char v : vars)
        std::cout << v << " | ";
    std::cout << "= |\n";

    for (size_t i = 0; i < vars.size(); i++)
        std::cout << "---|";
    std::cout << "---|\n";

    for (int i = 0; i < rows; i++)
    {
        std::cout << " ";
        std::map<char, bool> vmap;
        for (int j = 0; j < n; j++)
        {
            bool val = (i >> (n - j - 1)) & 1;
            vmap[vars[j]] = val;
            std::cout << val << " | ";
        }

        std::cout << eval(formula, vmap) << " |\n";
    }
}
int main()
{
    try
    {
        print_truth_table("AB&C|");
    }
    catch(const char *msg)
    {
        std::cout << "Error: " << msg << std::endl;
    }
}