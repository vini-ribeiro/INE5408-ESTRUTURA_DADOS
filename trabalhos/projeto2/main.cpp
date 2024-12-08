// Copyright 2024 Vinicius Henrique Ribeiro

#include <fstream>
#include <iostream>
#include <string>

#include "LeitorDIC.h"
#include "trie.h"

int main() {
    std::string file("dicionarios/dicionario1.dic");  // Abra o arquivo
    structures::Trie a;

    LeitorDIC l;
    l.abrir_arquivo(file);
    size_t chars_lidos = 0;
    while (l.ler_linha()) {
        a.insert(l.Palavra(), chars_lidos, l.Palavra().size() + l.Descricao().size() + 2);  // +2 para adicionar os colchetes []
        chars_lidos += l.Palavra().size() + l.Descricao().size() + 2;
        chars_lidos++;  // desloca para a próxima
    }

    std::string word;
    while (1) {  // leitura das palavras ate' encontrar "0"
        std::cin >> word;
        if (word.compare("0") == 0) {
            break;
        }
        size_t quantidade_prefixos = a.prefix_of(word);
        if (quantidade_prefixos > 0)
            std::cout << word << " is prefix of " << quantidade_prefixos << " words" << "\n";
        else
            std::cout << word << " is not prefix \n";

        if (a.contains(word)) {
            std::cout << "bear is at (" << a.posicao(word) << "," << a.comprimento(word) << ")" << "\n";
        }
    }

    return 0;
}