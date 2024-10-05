#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;


class Cenario {
  public:

    Cenario(string& texto, size_t indice_inicial) {

        size_t pos = indice_inicial;
        nome = proxima_tag_conteudo(texto, pos, "nome");
        altura = static_cast<size_t>( stoi( proxima_tag_conteudo(texto, pos, "altura") ) );
        largura = static_cast<size_t>( stoi( proxima_tag_conteudo(texto, pos, "largura") ) );
        x = static_cast<size_t>( stoi( proxima_tag_conteudo(texto, pos, "x") ) );
        y = static_cast<size_t>( stoi( proxima_tag_conteudo(texto, pos, "y") ) );
        matriz = matriz_remove_espacos( proxima_tag_conteudo(texto, pos, "matriz") );
        indice_final = pos;
        matriz_numerica = new int*[altura];
        for (size_t i = 0; i < altura; i++) {
            matriz_numerica[i] = new int[largura];
        }
        monta_matriz_numerica();
    }


    ~Cenario() {

        for (size_t i = 0; i < altura; ++i) {
            delete[] matriz_numerica[i];
        }
        delete[] matriz_numerica;
    };


    string nome;
    size_t altura;
    size_t largura;
    size_t x;
    size_t y;
    string matriz;
    int **matriz_numerica;
    size_t indice_final;

  private:

    string proxima_tag(string& texto, size_t& pos) {

        string tag = "";
        for ( ; pos < texto.length(); pos++) {
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


    string proximo_conteudo(string& texto, size_t& pos) {

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


    string proxima_tag_conteudo(string& texto, size_t& pos, string nome_tag) {

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


    void monta_matriz_numerica() {

        if (matriz.length() != largura * altura) {
            throw out_of_range("tamanho de matriz não condiz com altura * largura em monta_matriz_numerica");
        }

        size_t percorre_texto = 0;
        for (size_t i = 0; i < altura; ++i) {
            for (size_t j = 0; j < largura; ++j) {
                matriz_numerica[i][j] = matriz[percorre_texto++] - '0';
            }    
        }
    }
};


/**********************
    FUNÇÃO PRINCIPAL
***********************/
int main() {

    string filename;

    std::cin >> filename;  // nome do arquivo de entrada 
                           // (no 'executar': escrever pelo teclado;
                           //  no 'avaliar' : nome é passado pelos testes)

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

    // Exemplo de leitura do primeiro cenário - REMOVER ESTAS SAÍDAS DE TELA NA VERSÃO FINAL
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

    // Exemplo de leitura do segundo cenário (a partir do índice final de c1) - REMOVER ESTAS SAÍDAS DE TELA NA VERSÃO FINAL
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

    // Exemplo de leitura do primeiro cenário - REMOVER ESTAS SAÍDAS DE TELA NA VERSÃO FINAL
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
