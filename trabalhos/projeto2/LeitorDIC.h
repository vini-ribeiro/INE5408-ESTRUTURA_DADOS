// Copyright 2024 Vinicius Henrique Ribeiro

#ifndef _LEITORDIC_H_
#define _LEITORDIC_H_

#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

class LeitorDIC {
   public:
    LeitorDIC() : file_(nullptr), numero_linha_(0), palavra_(""), descricao_("") {}

    ~LeitorDIC() {
        if (file_->is_open()) file_->close();
        delete file_;
    }

    bool abrir_arquivo(std::string path_file) {
        file_ = new std::ifstream(path_file);
        if (!file_->is_open()) {
            std::cerr << "Erro ao abrir o arquivo!" << std::endl;
            return false;
        }
        return true;
    }

    bool ler_linha() {
        std::string linha;
        if (file_->is_open() && !file_->eof()) {
            std::getline(*file_, linha);
            numero_linha_++;
            extrai_dados(linha);
            return true;
        }
        return false;
    }

    std::string Palavra() { return palavra_; }

    std::string Descricao() { return descricao_; }

   private:
    void extrai_dados(std::string &linha) {
        size_t tam_linha = linha.size();
        size_t index     = 0;
        palavra_         = "";
        descricao_       = "";

        index++;
        while (tam_linha > index && linha[index] != ']') {
            palavra_ += linha[index++];
        }
        index++;
        while (index < linha.size()) {
            descricao_ += linha[index++];
        }
    }

    std::ifstream *file_;
    size_t numero_linha_;
    std::string palavra_;
    std::string descricao_;
};

#endif