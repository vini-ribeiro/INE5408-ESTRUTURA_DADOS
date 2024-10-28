#include "Cenario.h"
#include <cstddef>
#include <exception>
#include <fstream>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

#ifndef _ARQUIVOXML_H_
#define _ARQUIVOXML_H_

using namespace std;

class ArquivoXML {
  public:
    ArquivoXML() : descricaoValidadeXML_(""), texto_(""), xmlValido_(false) {
    }

    ~ArquivoXML() {
    }

    void limparDados() {
    	texto_.clear();
    	descricaoValidadeXML_.clear();
    	xmlValido_ = false;
    }

    void lerArquivo(string filename) {
        // Abertura do arquivo
        ifstream filexml(filename);
        if (!filexml.is_open()) {
            cerr << "Erro ao abrir o arquivo " << filename << endl;
            throw runtime_error("Erro no arquivo XML");
        }

        // Leitura do XML completo para 'texto'
        limparDados();
        char character;
        while (filexml.get(character)) {
            texto_ += character;
        }
    }

    bool validarXML() {

        string tag = "";
        stack<string> pilhaTags_;
        size_t pos = 0;

        for (; pos < texto_.length(); pos++) {
            if (texto_[pos] == '<') {
                pos++; // estava em <, passa para a primeira letra da tag
                while (texto_[pos] != '>') {
                    tag += texto_[pos];
                    pos++;
                }
                // pos++;                 // estava em >, passa para a primeira posição fora ou dentro da tag
                if (tag.length() == 0) { // tag não tem nome (vazia)
                    descricaoValidadeXML_ = "erro";
                    return xmlValido_;
                }
                if (tag.at(0) != '/') { // tag de abertura. Empilha
                    pilhaTags_.push(tag);
                    tag.clear();
                    continue;
                }
                tag.erase(0, 1);
                if (tag != pilhaTags_.top()) { // tag de fechamento difere da tag de abertura
                    descricaoValidadeXML_ = "erro";
                    return xmlValido_;
                }

                pilhaTags_.pop(); // desempilha devido ao fechamento da tag
                tag.clear();
            }
        }

        if (pilhaTags_.empty()) {
            xmlValido_ = 1;
            return xmlValido_;
        }

        descricaoValidadeXML_ = "erro";
        return xmlValido_;
    }

    size_t tamanhoTextoXML() {
        return texto_.length();
    }

    string Texto() {
        return texto_;
    }

    string descricaoValidadeXML() {
        return descricaoValidadeXML_;
    }

    bool XMLValido() {
    	return xmlValido_;
    }

  private:
    string descricaoValidadeXML_;
    string texto_;
    bool xmlValido_;
};

#endif

// void extrairCenarios() {

//     if (!xmlValido_)
//         return;

//     if (quantidadeCenarios_ < 1)
//         return;

//     Cenario *c = new Cenario(texto_, 0);
//     cenarios_.push_back(c);

//     for (size_t i = 0; i < quantidadeCenarios_; i++) {
// 		cenarios_.push_back(new Cenario(texto_, cenarios_.front()->indice_final));
//     }
// }