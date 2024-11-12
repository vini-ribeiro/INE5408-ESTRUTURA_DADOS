#include "binary_tree.h"

int main() {

    structures::BinaryTree<int> b;

    for (int i = 0; i < 20; ++i) {
        b.insert(i);
    }

    b.balance();

    return 0;
}