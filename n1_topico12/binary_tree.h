#include "array_list.h"

namespace structures {

template <typename T> class BinaryTree {
  public:
    BinaryTree();

    ~BinaryTree();

    void insert(const T &data);

    void remove(const T &data);

    bool contains(const T &data) const;

    bool empty() const;

    std::size_t size() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

  private:
    struct Node {
        explicit Node(const T &data_) {
            data = data_;
            left = nullptr;
            right = nullptr;
        }

        T data;
        Node *left;
        Node *right;

        void insert(const T &data_) {
            // COLOQUE SEU CÓDIGO AQUI... SE IMPLEMENTAÇÃO RECURSIVA
        }

        bool remove(const T &data_) {
            // COLOQUE SEU CÓDIGO AQUI... SE IMPLEMENTAÇÃO RECURSIVA
        }

        bool contains(const T &data_) const {
            if (data_ == data) {
                return true;
            } else if (data_ < data) {
                if (left != nullptr) {
                    return left->contains(data_);
                } else {
                    return false;
                }
            } else { // data_ > data
                if (right != nullptr) {
                    return right->contains(data_);
                } else {
                    return false;
                }
            }
        }

        void pre_order(ArrayList<T> &v) const {
            // COLOQUE SEU CÓDIGO AQUI...
        }

        void in_order(ArrayList<T> &v) const {
            // COLOQUE SEU CÓDIGO AQUI...
        }

        void post_order(ArrayList<T> &v) const {
            // COLOQUE SEU CÓDIGO AQUI...
        }
    };

    Node *root;
    std::size_t size_;
};

} // namespace structures

//-------------------------------------

template <typename T> structures::BinaryTree<T>::BinaryTree() {
    root = nullptr;
    size_ = 0;
}

template <typename T> structures::BinaryTree<T>::~BinaryTree() {
    // COLOQUE SEU CÓDIGO AQUI...
}

template <typename T> void structures::BinaryTree<T>::insert(const T &data) {
    // COLOQUE SEU CÓDIGO AQUI...
}

template <typename T> void structures::BinaryTree<T>::remove(const T &data) {
    // COLOQUE SEU CÓDIGO AQUI...
}

template <typename T>
bool structures::BinaryTree<T>::contains(const T &data) const {
    if (root != nullptr) {
        return root->contains(data);
    } else {
        return false;
    }
}

template <typename T> bool structures::BinaryTree<T>::empty() const {
    return size() == 0;
}

template <typename T> std::size_t structures::BinaryTree<T>::size() const {
    return size_;
}

template <typename T>
structures::ArrayList<T> structures::BinaryTree<T>::pre_order() const {
    structures::ArrayList<T> L;
    if (root != nullptr) {
        root->pre_order(L);
    }
    return L;
}

template <typename T>
structures::ArrayList<T> structures::BinaryTree<T>::in_order() const {
    // COLOQUE SEU CÓDIGO AQUI...
}

template <typename T>
structures::ArrayList<T> structures::BinaryTree<T>::post_order() const {
    // COLOQUE SEU CÓDIGO AQUI...
}
