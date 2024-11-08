#include "array_list.h"
#include <stdexcept>

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

            if (data > data_) {
                if (left == nullptr) {
                    Node *newNode = new Node(data_);
                    left = newNode;
                } else {
                    left->insert(data_);
                }
            }

            if (data < data_) {
                if (right == nullptr) {
                    Node *newNode = new Node(data_);
                    right = newNode;
                } else {
                    right->insert(data_);
                }
            }
        }

        Node *getMaxValueInSubTree(Node *node) {
            if (node == nullptr)
                return nullptr;

            if (node->right == nullptr)
                return node;

            return getMaxValueInSubTree(node->right);
        }

        Node *getMinValueInSubTree(Node *node) {
            if (node == nullptr)
                return nullptr;

            if (node->left == nullptr)
                return node;

            return getMinValueInSubTree(node->left);
        }

        Node *remove(Node *node, const T &data_) {
            // COLOQUE SEU CÓDIGO AQUI... SE IMPLEMENTAÇÃO RECURSIVA
            Node *aux, *filho;

            if (node == nullptr)
                return nullptr;

            if (node->data > data_) {
                node->left = remove(node->left, data_);
                return node;
            }

            if (node->data < data_) {
                node->right = remove(node->right, data_);
                return node;
            }

            if (node->left != nullptr && node->right != nullptr) {
                aux = getMinValueInSubTree(node->right);
                node->data = aux->data;
                node->right = remove(node->right, node->data);
                return node;
            }

            if (node->right != nullptr) {
                filho = node->right;
                return filho;
            }

            if (node->left != nullptr) {
                filho = node->left;
                return filho;
            }

            delete node;
            return nullptr;
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

        void pre_order(ArrayList<T> &v, Node *node) const {
            // COLOQUE SEU CÓDIGO AQUI...
            if (node == nullptr)
                return;
            v.push_back(node->data);
            pre_order(v, node->left);
            pre_order(v, node->right);
        }

        void in_order(ArrayList<T> &v, Node *node) const {
            // COLOQUE SEU CÓDIGO AQUI...
            if (node == nullptr)
                return;
            pre_order(v, node->left);
            v.push_back(node->data);
            pre_order(v, node->right);
        }

        void post_order(ArrayList<T> &v, Node *node) const {
            // COLOQUE SEU CÓDIGO AQUI...
            if (node == nullptr)
                return;
            pre_order(v, node->left);
            pre_order(v, node->right);
            v.push_back(node->data);
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
    if (root != nullptr) {
        structures::ArrayList<T> list_pre_order = root->pre_order();
        while (!list_pre_order.empty()) {
            remove(list_pre_order.pop_back());
        }
    }
}

template <typename T> void structures::BinaryTree<T>::insert(const T &data) {
    // COLOQUE SEU CÓDIGO AQUI...
    if (contains(data))
        throw std::out_of_range("Dado já está na árvore");

    if (root == nullptr) {
        root = new Node(data);
    } else {
        root->insert(data);
    }
    size_++;
}

template <typename T> void structures::BinaryTree<T>::remove(const T &data) {
    // COLOQUE SEU CÓDIGO AQUI...
    if (!contains(data))
        return;

    root->remove(root, data);
    size_--;
}

template <typename T> bool structures::BinaryTree<T>::contains(const T &data) const {
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

template <typename T> structures::ArrayList<T> structures::BinaryTree<T>::pre_order() const {
    structures::ArrayList<T> L;
    if (root != nullptr) {
        root->pre_order(L, root);
    }
    return L;
}

template <typename T> structures::ArrayList<T> structures::BinaryTree<T>::in_order() const {
    // COLOQUE SEU CÓDIGO AQUI...
    structures::ArrayList<T> L;
    if (root != nullptr) {
        root->in_order(L, root);
    }
    return L;
}

template <typename T> structures::ArrayList<T> structures::BinaryTree<T>::post_order() const {
    // COLOQUE SEU CÓDIGO AQUI...
    structures::ArrayList<T> L;
    if (root != nullptr) {
        root->post_order(L, root);
    }
    return L;
}
