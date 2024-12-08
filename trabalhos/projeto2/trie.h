// Copyright 2024 Vinicius Henrique Ribeiro

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

    void insert(const std::string &palavra, const size_t posicao, const size_t comprimento) {
        if (!contains(palavra)) {
            root_->n_prefixos_ += root_->insert(root_, palavra, 0, posicao, comprimento);
            size_ += palavra.size();
        }
    }

    bool contains(const std::string &palavra) const { return root_->contains(palavra); }

    size_t prefix_of(const std::string &palavra) const { return root_->prefix_of(palavra); }

    size_t posicao(const std::string &palavra) const {
        if (contains(palavra)) {
            return root_->posicao(palavra);
        }

        return 0;
    }

    size_t comprimento(const std::string &palavra) const {
        if (contains(palavra)) {
            return root_->comprimento(palavra);
        }

        return 0;
    }

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

        size_t insert(NoTrie *node, const std::string &palavra, size_t index, const size_t &posicao, const size_t &comprimento) {
            if (index >= palavra.size()) {
                node->posicao_     = posicao;
                node->comprimento_ = comprimento;
                node->n_prefixos_  = 1;
                return 1;
            }

            size_t index_filho = palavra[index] - 'a';
            if (node->filhos_[index_filho] == nullptr) {
                node->filhos_[index_filho] = new NoTrie(palavra[index]);
                node->n_prefixos_ += insert(node->filhos_[index_filho], palavra, ++index, posicao, comprimento);
                return 1;
            }

            node->n_prefixos_ += insert(node->filhos_[index_filho], palavra, ++index, posicao, comprimento);
            return 1;
        }

        bool contains(const std::string &palavra) const {
            const NoTrie *aux = get_node(this, palavra);

            return aux != nullptr && aux->comprimento_ > 0;
        }

        size_t prefix_of(const std::string &palavra) const {
            const NoTrie *aux = get_node(this, palavra);

            if (aux == nullptr) return 0;

            return aux->n_prefixos_;
        }

        size_t posicao(const std::string &palavra) const {
            const NoTrie *node = get_node(this, palavra);

            if (node == nullptr) return 0;

            return node->posicao_;
        }

        size_t comprimento(const std::string &palavra) const {
            const NoTrie *node = get_node(this, palavra);

            if (node == nullptr) return 0;

            return node->comprimento_;
        }

       private:
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