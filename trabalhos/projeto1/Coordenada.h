#ifndef _COORDENADA_H_
#define _COORDENADA_H_

#include <cstddef>

using namespace std;

class Coordenada {
  public:
    Coordenada(size_t x, size_t y) : x_(x), y_(y) {
    }

    size_t X() {
        return x_;
    }

    size_t Y() {
        return y_;
    }

  private:
    size_t x_;
    size_t y_;
};

#endif