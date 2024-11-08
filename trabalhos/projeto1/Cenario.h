#include <cstddef>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>

#ifndef _CENARIO_H_
#define _CENARIO_H_

#include "Coordenada.h"
#include <queue>

using namespace std;

class Cenario {
  public:
    Cenario() : nome_(""), altura_(0), largura_(0), x_(0), y_(0), matriz_(""), indice_final_(0), qt_ums_(0), matriz_numerica_(nullptr) {
    }

    ~Cenario() {
        if (matriz_numerica_ != nullptr) {
            for (size_t i = 0; i < altura_; ++i) {
                delete[] matriz_numerica_[i];
            }
            delete[] matriz_numerica_;
        }
    }

    // responsável por limpar todos os dados do cenario para uma nova utilização do objeto
    void limpa_cenario() {
        if (matriz_numerica_ != nullptr) {
            for (size_t i = 0; i < altura_; ++i) {
                delete[] matriz_numerica_[i];
            }
            delete[] matriz_numerica_;
        }
        matriz_numerica_ = nullptr;
    }

    void monta_cenario(string &texto, size_t indice_inicial) {

        size_t pos = indice_inicial;
        nome_ = proxima_tag_conteudo(texto, pos, "nome");
        altura_ = static_cast<size_t>(stoi(proxima_tag_conteudo(texto, pos, "altura")));
        largura_ = static_cast<size_t>(stoi(proxima_tag_conteudo(texto, pos, "largura")));
        x_ = static_cast<size_t>(stoi(proxima_tag_conteudo(texto, pos, "x")));
        y_ = static_cast<size_t>(stoi(proxima_tag_conteudo(texto, pos, "y")));
        matriz_ = matriz_remove_espacos(proxima_tag_conteudo(texto, pos, "matriz"));
        indice_final_ = pos;
        matriz_numerica_ = nullptr;
    }

    size_t resolveQuestao2() {
        // alocação da matriz para aplicação dos algoritimos
        aloca_matriz_dinamicamente();
        inicializa_matriz_numerica();

        queue<Coordenada *> fila_coordenadas;
        // criação da primeira coordenada
        fila_coordenadas.push(new Coordenada(x_, y_));
        if (matriz_[fila_coordenadas.front()->X() * largura_ + fila_coordenadas.front()->Y()] != '1') {
            delete fila_coordenadas.front();
            fila_coordenadas.pop();
        }

        size_t quantidade_ums = 0;

        while (!fila_coordenadas.empty()) {
            Coordenada *ptrCoord = fila_coordenadas.front();

            // vizinho acima (x-1, y)
            if (ptrCoord->X() - 1 >= 0 && ptrCoord->X() - 1 < altura_) {
                if (matriz_[(ptrCoord->X() - 1) * largura_ + ptrCoord->Y()] == '1' && matriz_numerica_[ptrCoord->X() - 1][ptrCoord->Y()] == 0) {
                    matriz_numerica_[ptrCoord->X() - 1][ptrCoord->Y()] = 1;
                    quantidade_ums++;
                    fila_coordenadas.push(new Coordenada(ptrCoord->X() - 1, ptrCoord->Y()));
                }
            }

            // vizinho abaixo (x+1, y)
            if (ptrCoord->X() + 1 < altura_) {
                if (matriz_[(ptrCoord->X() + 1) * largura_ + ptrCoord->Y()] == '1' && matriz_numerica_[ptrCoord->X() + 1][ptrCoord->Y()] == 0) {
                    matriz_numerica_[ptrCoord->X() + 1][ptrCoord->Y()] = 1;
                    quantidade_ums++;
                    fila_coordenadas.push(new Coordenada(ptrCoord->X() + 1, ptrCoord->Y()));
                }
            }

            // vizinho à esquerda (x, y-1)
            if (ptrCoord->Y() - 1 >= 0 && ptrCoord->Y() - 1 < largura_) {
                if (matriz_[(ptrCoord->X()) * largura_ + ptrCoord->Y() - 1] == '1' && matriz_numerica_[ptrCoord->X()][ptrCoord->Y() - 1] == 0) {
                    matriz_numerica_[ptrCoord->X()][ptrCoord->Y() - 1] = 1;
                    quantidade_ums++;
                    fila_coordenadas.push(new Coordenada(ptrCoord->X(), ptrCoord->Y() - 1));
                }
            }

            // vizinho à direita (x, y+1)
            if (ptrCoord->Y() + 1 < largura_) {
                if (matriz_[(ptrCoord->X()) * largura_ + ptrCoord->Y() + 1] == '1' && matriz_numerica_[ptrCoord->X()][ptrCoord->Y() + 1] == 0) {
                    matriz_numerica_[ptrCoord->X()][ptrCoord->Y() + 1] = 1;
                    quantidade_ums++;
                    fila_coordenadas.push(new Coordenada(ptrCoord->X(), ptrCoord->Y() + 1));
                }
            }

            fila_coordenadas.pop();
            delete ptrCoord;
        }
        qt_ums_ = quantidade_ums;
        return quantidade_ums;
    }

    string nome() const {
        return nome_;
    }

    size_t altura() const {
        return altura_;
    }

    size_t largura() const {
        return largura_;
    }

    size_t x() const {
        return x_;
    }

    size_t y() const {
        return y_;
    }

    string matriz() const {
        return matriz_;
    }

    size_t indice_final() const {
        return indice_final_;
    }

    size_t qt_ums() const {
        return qt_ums_;
    }

    size_t matriz_numerica(size_t x, size_t y) const {
        if (x > altura() || y > largura())
            throw out_of_range("valores invalidos");

        if (matriz_numerica_ == nullptr)
            throw out_of_range("matriz não foi inicializada");

        return matriz_numerica_[x][y];
    }

    void imprime_matriz_numerica() const {
        if (matriz_numerica_ != nullptr) {
            for (size_t i = 0; i < altura_; ++i) {
                for (size_t j = 0; j < largura_; ++j) {
                    cout << matriz_numerica_[i][j];
                }
                cout << endl;
            }
        }
        cout << endl;
    }

  private:
    void aloca_matriz_dinamicamente() {
        matriz_numerica_ = new int *[altura_];
        for (size_t i = 0; i < altura_; ++i) {
            matriz_numerica_[i] = new int[largura_];
        }
    }

    void inicializa_matriz_numerica() {
        for (size_t i = 0; i < altura_; ++i) {
            for (size_t j = 0; j < largura_; ++j) {
                matriz_numerica_[i][j] = 0;
            }
        }
    }

    string proxima_tag(string &texto, size_t &pos) {

        string tag = "";
        for (; pos < texto.length(); pos++) {
            if (texto[pos] == '<') {
                pos++;
                while (texto[pos] != '>') {
                    tag += texto[pos];
                    pos++;
                }
                pos++;
                return tag;
            }
        }
        return tag;
    }

    string proximo_conteudo(string &texto, size_t &pos) {

        string txt = "";
        while (texto[pos] != '<') {
            txt += texto[pos];
            pos++;
        }
        while (texto[pos] != '>') {
            pos++;
        }
        pos++;
        return txt;
    }

    string proxima_tag_conteudo(string &texto, size_t &pos, string nome_tag) {

        string tag = "";
        while (tag != nome_tag) {
            tag = proxima_tag(texto, pos);
        }
        return proximo_conteudo(texto, pos);
    }

    string matriz_remove_espacos(string texto) {

        string saida;
        for (size_t i = 0; i < texto.length(); i++) {
            if (texto[i] == '0' || texto[i] == '1') {
                saida += texto[i];
            }
        }
        return saida;
    }

    string nome_;
    size_t altura_;
    size_t largura_;
    size_t x_;
    size_t y_;
    string matriz_;
    size_t indice_final_;
    size_t qt_ums_;
    int **matriz_numerica_;
};

#endif