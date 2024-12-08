#include <cstdlib>
#include <iostream>

#include "avl_tree.h"

int main(void) {
    structures::AVLTree<int> avl;

    int arr[] = {10, 20, 30, 40, 50, 25, 5, 4, 3, 35};

    for (int i = 0; i < 10; ++i) {
        avl.insert(arr[i]);
        std::cerr << "inserção de " << arr[i] << " deixa altura "
                  << avl.height() << "\n";
    }

    std::cerr << "altura " << avl.height() << "\n";

    structures::ArrayList<int> pre_order_i = avl.pre_order();

    for (size_t i = 0; i < pre_order_i.size(); ++i) {
        std::cerr << pre_order_i.at(i) << " - ";
    }

    std::cerr << "\n";

    for (int i = 0; i < 10; ++i) {
        avl.remove(arr[i]);
        std::cerr << "remoção de " << arr[i] << " deixa altura " << avl.height()
                  << "\n";
    }

    std::cerr << "altura " << avl.height() << "\n";

    structures::ArrayList<int> pre_order_r = avl.pre_order();

    for (size_t i = 0; i < pre_order_r.size(); ++i) {
        std::cerr << pre_order_r.at(i) << " - ";
    }

    return 0;
}