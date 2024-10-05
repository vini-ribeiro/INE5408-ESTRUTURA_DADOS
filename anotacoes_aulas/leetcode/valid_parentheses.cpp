#include <iostream>
#include <string>
#include <stack>

class Solution {
public:
    bool isValid(std::string s) {
        std::stack<char> chares;

        size_t cont = 0;

        while (cont < s.size()) {
            if (s[cont] == '{' || s[cont] == '[' || s[cont] == '(') {
                chares.push(s[cont]);
            }
            if (s[cont] == '}') {
                if (chares.empty()) return false;
                if (chares.top() == '{') chares.pop();
                else return false;
            }
            if (s[cont] == ']') {
                if (chares.empty()) return false;
                if (chares.top() == '[') chares.pop();
                else return false;
            }
            if (s[cont] == ')') {
                if (chares.empty()) return false;
                if (chares.top() == '(') chares.pop();
                else return false;
            }
            cont++;
        }

        return chares.empty();
    }
};

int main(void)
{
    Solution s;
    std::cout << s.isValid("[]") << std::endl;
    return 0;
}