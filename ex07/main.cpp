#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <stack>
#include <stdexcept>

bool is_var(char c)
{
    return c >= 'A' && c <= 'Z';
}

std::vector<char> get_variables(const std::string& formula)
{
    std::set<char> vars;
    for (char c : formula)
    {
        if (is_var(c))
            vars.insert(c);
    }
    return std::vector<char>(vars.begin(), vars.end());
}

bool eval_rpn(const std::string& formula, const std::vector<char>& vars, int mask)
{
    std::stack<bool> st;

    for (char c : formula)
    {
        if (is_var(c))
        {
            int idx = 0;
            while (idx < (int)vars.size() && vars[idx] != c)
                idx++;

            if (idx == (int)vars.size())
                throw std::runtime_error("invalid variable");

            bool value = (mask >> idx) & 1;
            st.push(value);
        }
        else if (c == '!')
        {
            if (st.empty())
                throw std::runtime_error("invalid formula");
            bool a = st.top();
            st.pop();
            st.push(!a);
        }
        else if (c == '&')
        {
            if (st.size() < 2)
                throw std::runtime_error("invalid formula");
            bool b = st.top();
            st.pop();
            bool a = st.top();
            st.pop();
            st.push(a && b);
        }
        else if (c == '|')
        {
            if (st.size() < 2)
                throw std::runtime_error("invalid formula");
            bool b = st.top();
            st.pop();
            bool a = st.top();
            st.pop();
            st.push(a || b);
        }
        else if (c == '^')
        {
            if (st.size() < 2)
                throw std::runtime_error("invalid formula");
            bool b = st.top();
            st.pop();
            bool a = st.top();
            st.pop();
            st.push((a || b) && !(a && b));
        }
        else
        {
            throw std::runtime_error("invalid operator");
        }
    }

    if (st.size() != 1)
        throw std::runtime_error("invalid formula");

    return st.top();
}

bool sat(const std::string& formula)
{
    std::vector<char> vars = get_variables(formula);
    int n = vars.size();
    int total = 1 << n;

    for (int mask = 0; mask < total; mask++)
    {
        if (eval_rpn(formula, vars, mask))
            return true;
    }

    return false;
}

int main()
{
    try
    {
        std::cout << sat("AB|") << std::endl;
        std::cout << sat("AB&") << std::endl;
        std::cout << sat("AA!&") << std::endl;
        std::cout << sat("AA^") << std::endl;
    }
    catch (const char *msg)
    {
        std::cout << "runtime error: " << msg << std::endl;
    }

    return 0;
}