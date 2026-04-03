#include <iostream>
#include <string>
#include <vector>
#include <stack>

bool is_var(char c)
{
    return c >= 'A' && c <= 'Z';
}

void split_rpn(const std::string& s, std::string& lhs, std::string& rhs) 
{
    if (s.empty())
        throw std::runtime_error("invalid formula");
    int i = s.size() - 2;
    int target = 1;
    
    int end_rhs = i;
    while (i >= 0 && target > 0)
    {
        if (is_var(s[i]))
            target--;
        else if (s[i] != '!')
            target++;
        i--;
    }
    rhs = s.substr(i + 1, end_rhs - i);
    lhs = s.substr(0, i + 1);
}

std::string negate_rpn_iterative(std::string s) 
{
    if (s.empty())
        throw std::runtime_error("invalid formula: leftover values");
    
    if (s.size() == 1 && is_var(s[0]))
        return s + "!";
    if (s.back() == '!') 
    {
        std::string sub = s.substr(0, s.size() - 1);
        if (sub.back() == '!')
            return sub.substr(0, sub.size() - 1);
        if (sub.size() == 1 && is_var(sub[0]))
            return sub;
    }

    // Application de De Morgan : !(A B op)
    char op = s.back();
    std::string lhs, rhs;
    split_rpn(s, lhs, rhs);

    if (op == '&')
        return negate_rpn_iterative(lhs) + negate_rpn_iterative(rhs) + "|";
    if (op == '|')
        return negate_rpn_iterative(lhs) + negate_rpn_iterative(rhs) + "&";

    return s + "!";
}

std::string negation_normal_form(const std::string& formula)
{
    std::stack<std::string> st;

    for (char c : formula) 
    {
        if (is_var(c))
            st.push(std::string(1, c));
        else if (c == '!')
        {
            if (st.empty())
                continue;
            std::string a = st.top();
            st.pop();
            st.push(negate_rpn_iterative(a));
        }
        else if (c == '&' || c == '|')
        {
            if (st.size() < 2)
                continue;
            std::string b = st.top();
                st.pop();
            std::string a = st.top();
            st.pop();
            st.push(a + b + c);
        }
        else if (c == '>')
        {
            if (st.size() < 2)
                continue;
            std::string b = st.top(); st.pop();
            std::string a = st.top(); st.pop();
            // A B >  =>  !A B |
            st.push(negate_rpn_iterative(a) + b + "|");
        }
        else if (c == '=')
        {
            if (st.size() < 2)
                continue;
            std::string b = st.top();
                st.pop();
            std::string a = st.top();
                st.pop();
            std::string term1 = a + b + "&";
            std::string term2 = negate_rpn_iterative(a) + negate_rpn_iterative(b) + "&";
            st.push(term1 + term2 + "|");
        }
    }

    if (st.empty())
        throw std::runtime_error("invalid formula");
    return st.top();
}

std::string distribute(std::string s)
{
    if (s.size() == 1)
        return s;

    char op = s.back();

    if (op == '|' || op == '&')
    {
        std::string lhs, rhs;
        split_rpn(s, lhs, rhs);

        lhs = distribute(lhs);
        rhs = distribute(rhs);

        // cas important
        if (op == '|')
        {
            // A | (B & C)
            if (rhs.back() == '&')
            {
                std::string b, c;
                split_rpn(rhs, b, c);
                return distribute(lhs + b + "|") +  distribute(lhs + c + "|") + "&";
            }

            // (A & B) | C
            if (lhs.back() == '&')
            {
                std::string a, b;
                split_rpn(lhs, a, b);
                return distribute(a + rhs + "|") +  distribute(b + rhs + "|") + "&";
            }
        }

        return lhs + rhs + op;
    }

    return s;
}

std::string conjunctive_normal_form(const std::string& formula)
{
    std::string nnf = negation_normal_form(formula);
    return distribute(nnf);
}

int main()
{
    try
    {
        std::cout << conjunctive_normal_form("AB&!") << std::endl;
        std::cout << conjunctive_normal_form("AB|!") << std::endl;
        std::cout << conjunctive_normal_form("AB|C&") << std::endl;
        std::cout << conjunctive_normal_form("AB|C|D|") << std::endl;
        std::cout << conjunctive_normal_form("AB&C&D&") << std::endl;
        std::cout << conjunctive_normal_form("AB&!C!|") << std::endl;
        std::cout << conjunctive_normal_form("AB|!C!&") << std::endl;
    }
    catch(const char *msg)
    {
        std::cout << "Error: " << msg << std::endl;
    }
  
    return 0;
}