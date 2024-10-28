#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main(void) {

    string nome("vinicius");
    string sla("gosto");
    string ten("/vinicius");
    // std::cout << "sla" << std::endl;
    std::stack<string> pilha;

    pilha.push(nome);
    pilha.push(sla);
    pilha.push(ten);

    cout << (ten == nome) << endl;
    ten.erase(0, 1);
    cout << (ten == nome) << endl;

    return 0;
}