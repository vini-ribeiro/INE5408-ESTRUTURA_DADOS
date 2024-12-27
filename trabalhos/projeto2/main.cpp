// Copyright 2024 Vinicius Henrique Ribeiro e Enzo Amaral custodio

#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

#include "LeitorDIC.h"
#include "trie.h"

int main() {
    std::string filename;

    std::cin >> filename;  // entrada
    structures::Trie trie;

    LeitorDIC leitor;                // cria objeto para ler o arquivo .dic
    leitor.abrir_arquivo(filename);  // passa o path do arquivo

    //	começa a leitura do arquivo
    size_t chars_lidos = 0;  // var para contabilizar quantos chars tem em uma
                             // linha do dicionário (palavra + descrição)
    while (leitor.ler_linha()) {
        // pega o comprimento da linha
        size_t comprimento_linha = leitor.Palavra().size() + leitor.Descricao().size() + 2;

        // insere na Trie
        trie.insert(leitor.Palavra(), chars_lidos,
                    comprimento_linha);  // +2 para adicionar os colchetes []

        // contabiliza o total lido de chars
        chars_lidos += comprimento_linha;
        chars_lidos++;  // desloca para a próxima
    }

    // var para pegar e entrada
    std::string word;
    while (1) {  // leitura das palavras ate' encontrar "0"
        std::cin >> word;
        if (word.compare("0") == 0) {
            break;
        }

        // pega quantos prefixos tem a palavra
        size_t quantidade_prefixos = trie.prefix_of(word);

        // caso tenha, exibe de quantos
        if (quantidade_prefixos > 0)
            std::cout << word << " is prefix of " << quantidade_prefixos << " words" << "\n";
        else
            std::cout << word << " is not prefix\n";

        // caso contenha, exibe a localização no dic
        if (trie.contains(word)) {
            std::cout << word << " is at (" << trie.posicao(word) << "," << trie.comprimento(word) << ")" << "\n";
        }
    }

    return 0;
}