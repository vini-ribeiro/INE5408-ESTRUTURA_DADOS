#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "ArquivoXML.h"
#include "Cenario.h"

using namespace std;

// Alunos: VINICIUS HENRIQUE RIBEIRO

int main() {

    string filename;

    std::cin >> filename;

    ArquivoXML a;
    a.lerArquivo(filename);
    a.validarXML();
    if (!a.XMLValido()) {
        cout << a.descricaoValidadeXML() << endl;
        return 1;
    }

    string texto = a.Texto();

    Cenario c;

    size_t cont = 0;
    while (cont < a.qtCenario()) {
        cont++;
        c.limpa_cenario();
        c.monta_cenario(texto, c.indice_final());
        cout << c.nome() << " ";
        c.resolveQuestao2();
        cout << c.qt_ums() << endl;
    }

    return 0;
}
