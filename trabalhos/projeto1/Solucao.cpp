#include <cstddef>
#include <string>

using namespace std;

class Solucao {

  public:
    Solucao() : nome_(""), altura_(0), largura_(0), matriz_(nullptr), x_(0), y_(0), quantidadeDeUms_(0) {
    }

    Solucao(string nome, string matriz, size_t altura, size_t largura, size_t x, size_t y)
        : nome_(nome), altura_(altura), largura_(largura), x_(x), y_(y), quantidadeDeUms_(0) {
        	
        matriz_ = new int *[altura];
        for (size_t i = 0; i < altura; i++) {
            matriz_[i] = new int[largura];
        }

        size_t k = 0;
        for (size_t i = 0; i < altura; ++i) {
            for (size_t j = 0; j < largura; ++j) {
                matriz_[i][j] = matriz[k] - '0';
                k++;
            }
        }
    }

    ~Solucao() {
        for (size_t i = 0; i < altura_; i++) {
            delete[] matriz_[i];
        }
        delete[] matriz_;
    }

  private:
    string nome_;
    size_t altura_;
    size_t largura_;
    int **matriz_;
    size_t x_, y_;
    size_t quantidadeDeUms_;
};