#include <iostream>
#include <stack>
#include <vector>
#include <set>
#include <map>
#include <string>

static std::vector<char> get_vars(const std::string &f)
{
    std::set<char> s;
    for (char c : f)
        if (c >= 'A' && c <= 'Z')
            s.insert(c);
    return std::vector<char>(s.begin(), s.end());
}

static bool eval(const std::string &f, std::map<char, bool> &v)
{
    std::stack<bool> st;

    for (char c : f)
    {
        if (c >= 'A' && c <= 'Z')
            st.push(v[c]);
        else if (c == '!')
        {
            bool a = st.top();
            st.pop();
            st.push(!a);
        }
        else
        {
            bool b = st.top();
            st.pop();
            bool a = st.top();
            st.pop();

            if (c == '&') st.push(a && b);
            else if (c == '|') st.push(a || b);
            else if (c == '^') st.push(a ^ b);
            else if (c == '>') st.push(!a || b);
            else if (c == '=') st.push(a == b);
        }
    }
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
    {
        std::cout << "---";
        if (i + 1 < vars.size())
            std::cout << "|";
    }
    std::cout << "|---|\n";

    for (int i = 0; i < rows; i++)
    {
        std::map<char, bool> v;
        std::cout << " ";
        for (int j = 0; j < n; j++)
        {
            bool val = (i >> (n - j - 1)) & 1;
            v[vars[j]] = val;
            std::cout << val << " | ";
        }

        std::cout << eval(formula, v) << " |\n";
    }
}

int main()
{
    print_truth_table("AB&C|");
}