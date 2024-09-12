// Copyright [2022] Vinicius Henrique Ribeiro
#include <iostream>
#include <string>

#include "pilha.h"

bool verificaChaves(std::string trecho_programa) {
    bool resposta = true;
    int  tamanho  = trecho_programa.length();
    structures::ArrayStack<char> pilha(500);
    
    for (int i = 0; i < tamanho; i++) {
        if (trecho_programa[i] == '{') pilha.push(trecho_programa[i]);
        if (trecho_programa[i] == '}') {
            if (pilha.empty()) {
                resposta = false;
                break;
            }
            pilha.pop();
        }
    }
    if (!pilha.empty()) resposta = false;
    
    return resposta;
}


int main() {
    std::string trecho_programa = "int main() {\n    std::string trecho_programa = \"{UFSC}\";\n    bool ok = verificaChaves(trecho_programa);\n    if (ok) {\n        std::cout << \"Tudo certo\" << std::endl;\n    } else {\n        std::cout << \"Há problema\" << std::endl;\n    }\n    return 0;\n}\n";
    bool ok = verificaChaves(trecho_programa);
    if (ok) {
        std::cout << "Tudo certo" << std::endl;
    } else {
        std::cout << "Há problema" << std::endl;
    }
    return 0;
}