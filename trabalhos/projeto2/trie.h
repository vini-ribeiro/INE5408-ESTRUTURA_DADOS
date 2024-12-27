// Copyright 2024 Vinicius Henrique Ribeiro e Enzo Amaral custodio

#ifndef _TRIE_H_
#define _TRIE_H_

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

namespace structures {

class Trie {
   public:
    Trie() : size_(0) { root_ = new NoTrie(); }

    ~Trie() { delete root_; }

    // função que chama o insert da classe privada NoTrie
    void insert(const std::string &palavra, const size_t posicao, const size_t comprimento) {
        // verifica se já contém a palavra
        if (!contains(palavra)) {
            // o retorno é somado na quantidade de prefixos do nodo chamador
            root_->insert(root_, palavra, 0, posicao, comprimento);
            root_->n_prefixos_++;
            // incrementa a quantidade de palavras na Trie
            size_ += palavra.size();
        }
    }

    // retorna true se contém palavra
    bool contains(const std::string &palavra) const { return root_->contains(palavra); }

    // quantidade de prefixos de uma string
    size_t prefix_of(const std::string &palavra) const { return root_->prefix_of(palavra); }

    // pega a posição da palavra no arquivo dic
    size_t posicao(const std::string &palavra) const {
        if (contains(palavra)) {
            return root_->posicao(palavra);
        }

        return 0;
    }

    // quantidade de chars da palavra + descrição
    size_t comprimento(const std::string &palavra) const {
        if (contains(palavra)) {
            return root_->comprimento(palavra);
        }

        return 0;
    }

    // true se vazia
    bool empty() const { return size_ == 0; }

    std::size_t size() const { return size_; }

   private:
    struct NoTrie {
        NoTrie() : letra_(0), posicao_(0), comprimento_(0), n_prefixos_(0) {}

        explicit NoTrie(char letra) : letra_(letra), posicao_(0), comprimento_(0), n_prefixos_(0) {}

        ~NoTrie() {
            for (int i = 0; i < 26; ++i) {
                delete filhos_[i];
            }
        }

        char letra_;
        NoTrie *filhos_[26] = {};
        size_t posicao_;      // localização do primeiro char no texto (dicionario)
        size_t comprimento_;  // comprimento da palavra + descrição
        size_t n_prefixos_;

        void insert(NoTrie *node, const std::string &palavra, size_t index, const size_t &posicao, const size_t &comprimento) {
            // pega o index do filho
            size_t index_filho = palavra[index] - 'a';
            // quando estiver na última letra da palavra, adiciona os dados (comprimento, posição e númerod e prefixos) ao nodo
            if (index >= palavra.size()) {
                node->posicao_     = posicao;
                node->comprimento_ = comprimento;
                node->n_prefixos_  = 1;
            } else if (node->filhos_[index_filho] == nullptr) {  // adiciona uma letra nos filhos caso o nodo atual não tenha
                node->filhos_[index_filho] = new NoTrie(palavra[index]);
                insert(node->filhos_[index_filho], palavra, ++index, posicao, comprimento);
                node->n_prefixos_++;
            } else {  // nodo atual tem filho mas ainda não é a última letra
                insert(node->filhos_[index_filho], palavra, ++index, posicao, comprimento);
                node->n_prefixos_++;
            }
        }

        bool contains(const std::string &palavra) const {
            const NoTrie *aux = get_node(this, palavra);

            return aux != nullptr && aux->comprimento_ > 0;
        }

        // vai até a último nodo para retornar o número de prefixos
        size_t prefix_of(const std::string &palavra) const {
            const NoTrie *aux = get_node(this, palavra);

            if (aux == nullptr) return 0;

            return aux->n_prefixos_;
        }

        // vai até a último nodo para retornar a posição no dic
        size_t posicao(const std::string &palavra) const {
            const NoTrie *node = get_node(this, palavra);

            if (node == nullptr) return 0;

            return node->posicao_;
        }

        // vai até a último nodo para retornar o comprimento
        size_t comprimento(const std::string &palavra) const {
            const NoTrie *node = get_node(this, palavra);

            if (node == nullptr) return 0;

            return node->comprimento_;
        }

       private:
        // auxiliar para posicionar um ponteiro para o nodo que guarda a última letra da palavra no argumento
        const NoTrie *get_node(const NoTrie *node, const std::string &palavra) const {
            if (node == nullptr) return nullptr;

            size_t i_palavra = 0;

            while (i_palavra < palavra.size()) {
                int i_alfabeto = palavra[i_palavra] - 'a';
                if (node->filhos_[i_alfabeto] == nullptr) {
                    return nullptr;
                }
                node = node->filhos_[i_alfabeto];
                i_palavra++;
            }

            return node;
        }
    };

    NoTrie *root_;
    std::size_t size_;
};

}  // namespace structures

#endif