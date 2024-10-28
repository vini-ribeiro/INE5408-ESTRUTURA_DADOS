#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "ArquivoXML.h"
#include "Cenario.h"

using namespace std;

/**********************
    FUNÇÃO PRINCIPAL
***********************/
int main() {

    string filename("cenarios6.xml");

    // std::cin >> filename; // nome do arquivo de entrada
    // (no 'executar': escrever pelo teclado;
    //  no 'avaliar' : nome é passado pelos testes)

    ArquivoXML a;
    a.lerArquivo(filename);
    a.validarXML();
    if (!a.XMLValido()) {
    	cout << a.descricaoValidadeXML() << endl;
    	return 0;
    }

    cout << a.Texto() << endl;

    return 0;

    // Abertura do arquivo
    ifstream filexml(filename);
    if (!filexml.is_open()) {
        cerr << "Erro ao abrir o arquivo " << filename << endl;
        throw runtime_error("Erro no arquivo XML");
    }

    // Leitura do XML completo para 'texto'
    string texto;
    char character;
    while (filexml.get(character)) {
        texto += character;
    }

    // ----------------------------
    // Sugestão de código para a PARTE 2 do projeto

    // Exemplo de leitura do primeiro cenário - REMOVER ESTAS SAÍDAS DE TELA NA
    // VERSÃO FINAL
    Cenario c1(texto, 0);

    cout << "nome   : " << c1.nome << endl;
    cout << "altura : " << c1.altura << endl;
    cout << "largura: " << c1.largura << endl;
    cout << "x      : " << c1.x << endl;
    cout << "y      : " << c1.y << endl;
    cout << "matriz : " << c1.matriz << endl << endl;
    for (size_t i = 0; i < c1.altura; ++i) {
        for (size_t j = 0; j < c1.largura; ++j) {
            cout << c1.matriz_numerica[i][j];
        }
        cout << endl;
    }

    // Exemplo de leitura do segundo cenário (a partir do índice final de c1) -
    // REMOVER ESTAS SAÍDAS DE TELA NA VERSÃO FINAL
    Cenario c2(texto, c1.indice_final);

    cout << "nome   : " << c2.nome << endl;
    cout << "altura : " << c2.altura << endl;
    cout << "largura: " << c2.largura << endl;
    cout << "x      : " << c2.x << endl;
    cout << "y      : " << c2.y << endl;
    cout << "matriz : " << c2.matriz << endl << endl;
    for (size_t i = 0; i < c2.altura; ++i) {
        for (size_t j = 0; j < c2.largura; ++j) {
            cout << c2.matriz_numerica[i][j];
        }
        cout << endl;
    }

    // Exemplo de leitura do primeiro cenário - REMOVER ESTAS SAÍDAS DE TELA NA
    // VERSÃO FINAL
    Cenario c3(texto, c2.indice_final);

    cout << "nome   : " << c3.nome << endl;
    cout << "altura : " << c3.altura << endl;
    cout << "largura: " << c3.largura << endl;
    cout << "x      : " << c3.x << endl;
    cout << "y      : " << c3.y << endl;
    cout << "matriz : " << c3.matriz << endl << endl;
    for (size_t i = 0; i < c3.altura; ++i) {
        for (size_t j = 0; j < c3.largura; ++j) {
            cout << c3.matriz_numerica[i][j];
        }
        cout << endl;
    }

    /*

       COLOQUE SEU CÓDIGO AQUI

    */

    return 0;
}
