#include <iostream>
#include <stdexcept>
#include <string>

#ifndef _CENARIO_H_
#define _CENARIO_H_

using namespace std;

class Cenario {
  public:
    Cenario(string &texto, size_t indice_inicial) {

        size_t pos = indice_inicial;
        nome = proxima_tag_conteudo(texto, pos, "nome");
        altura = static_cast<size_t>(stoi(proxima_tag_conteudo(texto, pos, "altura")));
        largura = static_cast<size_t>(stoi(proxima_tag_conteudo(texto, pos, "largura")));
        x = static_cast<size_t>(stoi(proxima_tag_conteudo(texto, pos, "x")));
        y = static_cast<size_t>(stoi(proxima_tag_conteudo(texto, pos, "y")));
        matriz = matriz_remove_espacos(proxima_tag_conteudo(texto, pos, "matriz"));
        indice_final = pos;
    }

    ~Cenario() {
    }

    string nome;
    size_t altura;
    size_t largura;
    size_t x;
    size_t y;
    string matriz;
    size_t indice_final;

  private:
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
};


#endif