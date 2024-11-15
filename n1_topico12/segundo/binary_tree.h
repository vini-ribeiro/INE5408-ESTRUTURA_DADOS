//!  Copyright [2024] VINICIUS HENRIQUE RIBEIRO

#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H

#include "./array_list.h"
#include <iostream>

namespace structures {

//! Classe Árvore binária
template <typename T> class BinaryTree {
  public:
    //! ...
    BinaryTree();
    //! ...
    ~BinaryTree();
    //! ...
    void insert(const T &data);
    //! ...
    void remove(const T &data);
    //! ...
    bool contains(const T &data) const;
    //! ...
    bool empty() const;
    //! ...
    std::size_t size() const;
    //! ...
    ArrayList<T> pre_order() const;
    //! ...
    ArrayList<T> in_order() const;
    //! ...
    ArrayList<T> post_order() const;

    //******************************************************************
    // Prova prática - implementações necessárias:

    // (1) determinação da altura da árvore:
    int height();

    // (2) contagem do número de folhas:
    int leaves();

    // (3) criação de uma lista com o menor (mínimo) e o maior (máximo)
    //     valor da árvore:
    ArrayList<T> limits();

    // (4) criação de uma duplicação, em memória, da árvore:
    BinaryTree<T> clone();

    // (5) remove nós pelo número de seus filhos:
    void filter(int n_child);

    // (6) criação de um nova árvore que tenha todos os valores e a
    //     menor altura possível, ou seja, balanceada com base apenas
    //     no estabelecimento de uma nova ordem de inserção:
    BinaryTree<T> balance();

    //******************************************************************

  private:
    struct Node {
        //! Construtor
        explicit Node(const T &data) : data_{data} {
        }

        //! Destrutor
        ~Node() {
            delete left_;
            delete right_;
        }

        size_t level_{0};
        T data_;
        Node *left_{nullptr};
        Node *right_{nullptr};

        //! Inserção
        void insert(const T &data) {
            /*
                COPIE AQUI O CÓDIGO DO EXERCÍCIO ANTERIOR ...
            */
            Node *aux = this;
            while (aux != nullptr) {
                if (data < aux->data_) {
                    if (aux->left_ == nullptr) {
                        aux->left_ = new Node(data);
                        aux->left_->level_ = aux->level_ + 1;
                        break;
                    }
                    aux = aux->left_;
                } else {
                    if (aux->right_ == nullptr) {
                        aux->right_ = new Node(data);
                        aux->right_->level_ = aux->level_ + 1;
                        break;
                    }
                    aux = aux->right_;
                }
            }
        }

        //! Remoção
        bool remove(const T &data, Node **root) {
            bool existe = false;
            /*
                COPIE AQUI O CÓDIGO DO EXERCÍCIO ANTERIOR ...
            */
            // verificar a existência pode ser meio inútil, já que no pior caso o nodo existe (é o mais comum)
            if ((*root)->contains(data)) {
                *root = (*root)->remove(data, *root, existe);
            }
            return existe;
        }

        //! Contém
        bool contains(const T &data) const {
            bool existe = false;
            /*
                COPIE AQUI O CÓDIGO DO EXERCÍCIO ANTERIOR ...
            */
            Node *aux = nullptr;
            if (this->data_ == data) {
                return true;
            } else if (data < this->data_) {
                aux = this->left_;
            } else {
                aux = this->right_;
            }

            while (aux != nullptr) {
                if (data < aux->data_) {
                    aux = aux->left_;
                } else if (data > aux->data_) {
                    aux = aux->right_;
                } else {
                    existe = true;
                    break;
                }
            }

            return existe;
        }

        //! Pré ordem
        void pre_order(ArrayList<T> &v) const {
            v.push_back(data_);
            if (left_ != nullptr)
                left_->pre_order(v);
            if (right_ != nullptr)
                right_->pre_order(v);
        }

        //! Em ordem
        void in_order(ArrayList<T> &v) const {
            /*
                COPIE AQUI O CÓDIGO DO EXERCÍCIO ANTERIOR ...
            */
            if (left_ != nullptr)
                left_->in_order(v);
            v.push_back(data_);
            if (right_ != nullptr)
                right_->in_order(v);
        }

        //! Pós ordem
        void post_order(ArrayList<T> &v) const {
            /*
                COPIE AQUI O CÓDIGO DO EXERCÍCIO ANTERIOR ...
            */
            if (left_ != nullptr)
                left_->post_order(v);
            if (right_ != nullptr)
                right_->post_order(v);
            v.push_back(data_);
        }

      private:
        //! Complemento da funcão de remoção
        Node *remove(const T &data, Node *arv, bool &deleted) {
            Node *temp = nullptr;
            /*
                COPIE AQUI O CÓDIGO DO EXERCÍCIO ANTERIOR ...
            */
            if (arv == nullptr) {
                deleted = false;
                return nullptr;
            }

            if (data < arv->data_) {
                deleted = false;
                arv->left_ = remove(data, arv->left_, deleted);
                return arv;
            }

            if (data > arv->data_) {
                deleted = false;
                arv->right_ = remove(data, arv->right_, deleted);
                return arv;
            }

            if (arv->left_ != nullptr && arv->right_ != nullptr) {
                Node *min = arv->right_->minimum();
                arv->data_ = min->data_;
                deleted = true;
                arv->right_ = remove(min->data_, arv->right_, deleted);
                return arv;
            }

            if (arv->left_ != nullptr) {
                temp = arv->left_;
                arv->left_ = nullptr;
                delete arv;
                deleted = true;
                return temp;
            }

            if (arv->right_ != nullptr) {
                temp = arv->right_;
                arv->right_ = nullptr;
                delete arv;
                deleted = true;
                return temp;
            }

            delete arv;
            deleted = true;

            return nullptr;
        }

        //! Encontrar o menor
        Node *minimum() {
            if (left_ == nullptr)
                return this;
            return left_->minimum();
        }
    };

    void balance(BinaryTree<T> &b, ArrayList<T> &v, int inf, int sup) {
        if (inf > sup)
            return;

        int center = (sup + inf) / 2;
        b.insert(v.at(center));
        balance(b, v, inf, center - 1);
        balance(b, v, center + 1, sup);
    }

    Node *root_{nullptr};
    std::size_t size_{0};
};

//******************************************************************
// Prova prática - implementações necessárias:

//! (1) determinação da altura da árvore:
template <typename T> int BinaryTree<T>::height() {
    /*
        COLOQUE SEU CÓDIGO AQUI ...
    */
    if (empty())
        return -1;

    ArrayList<Node *> fila;
    fila.push_back(root_);
    Node *aux;
    int max_h = 0;
    while (!fila.empty()) {
        aux = fila.pop_front();
        if (aux->left_ == nullptr && aux->right_ == nullptr) {
            if ((int) aux->level_ > max_h)
                max_h = aux->level_;
        }
        if (aux->left_ != nullptr) {
            fila.push_back(aux->left_);
        }
        if (aux->right_ != nullptr) {
            fila.push_back(aux->right_);
        }
    }

    return max_h;
}

//! (2) contagem do número de folhas:
template <typename T> int BinaryTree<T>::leaves() {
    /*
        COLOQUE SEU CÓDIGO AQUI ...
    */
    if (empty())
        return 0;

    ArrayList<Node *> fila;
    fila.push_back(root_);
    Node *aux;
    int l = 0;
    while (!fila.empty()) {
        aux = fila.pop_front();
        if (aux->left_ != nullptr) {
            fila.push_back(aux->left_);
        }
        if (aux->right_ != nullptr) {
            fila.push_back(aux->right_);
        }
        if (aux->left_ == nullptr && aux->right_ == nullptr) {
            l++;
        }
    }
    return l;
}

//! (3) criação de uma lista com o menor (mínimo) e o maior (máximo)
//!     valor da árvore:
template <typename T> ArrayList<T> BinaryTree<T>::limits() {
    ArrayList<T> L(2);
    /*
        COLOQUE SEU CÓDIGO AQUI ...
    */
    Node *aux = root_;

    while (aux->left_ != nullptr) {
        aux = aux->left_;
    }
    L.push_back(aux->data_);

    aux = root_;

    while (aux->right_ != nullptr) {
        aux = aux->right_;
    }
    L.push_back(aux->data_);

    return L;
}

//! (4) criação de uma duplicação, em memória, da árvore:
template <typename T> BinaryTree<T> BinaryTree<T>::clone() {
    BinaryTree<T> C;
    /*
        COLOQUE SEU CÓDIGO AQUI ...
    */
    ArrayList<T> pre_ord = pre_order();
    while (!pre_ord.empty()) {
        C.insert(pre_ord.pop_front());
    }
    return C;
}

//! (5) remove nós pelo número de seus filhos:
template <typename T> void BinaryTree<T>::filter(int n_child) {
    /*
        COLOQUE SEU CÓDIGO AQUI ...
    */
    if (empty())
        throw std::out_of_range("Empty tree");

    ArrayList<Node *> fila;
    fila.push_back(root_);
    Node *aux;
    while (!fila.empty()) {
        aux = fila.pop_front();
        if (aux->left_ != nullptr) {
            fila.push_back(aux->left_);
        }
        if (aux->right_ != nullptr) {
            fila.push_back(aux->right_);
        }
        if ((aux->left_ != nullptr) + (aux->right_ != nullptr) == n_child) {
            remove(aux->data_);
        }
    }
}

//! (6) criação de um nova árvore que tenha todos os valores e a
//!     menor altura possível, ou seja, balanceada com base apenas
//!     no estabelecimento de uma nova ordem de inserção:
template <typename T> BinaryTree<T> BinaryTree<T>::balance() {
    BinaryTree<T> B;
    /*
        COLOQUE SEU CÓDIGO AQUI ...
    */
    if (empty())
        return B;

    ArrayList<T> V = in_order();

    balance(B, V, 0, V.size() - 1);

    return B;
}

//******************************************************************

//! Construtor
template <typename T> BinaryTree<T>::BinaryTree() {
}

//! Destrutor
template <typename T> BinaryTree<T>::~BinaryTree() {
    delete root_;
}

//! Inserção
template <typename T> void BinaryTree<T>::insert(const T &data) {
    if (empty()) {
        root_ = new Node(data);
        if (root_ == nullptr)
            throw std::out_of_range("FUll tree!");
    } else {
        root_->insert(data);
    }
    ++size_;
}

// Remoção
template <typename T> void BinaryTree<T>::remove(const T &data) {
    if (empty())
        throw std::out_of_range("Empty tree");

    if (size() != 1u) {
        if (root_->remove(data, &root_))
            --size_;
    } else {
        if (root_->data_ == data) {
            delete root_;
            root_ = nullptr;
            --size_;
        }
    }
}

//! Contém
template <typename T> bool BinaryTree<T>::contains(const T &data) const {
    if (empty())
        return false;
    return root_->contains(data);
}

//! Vazio
template <typename T> bool BinaryTree<T>::empty() const {
    return size() == 0;
}

//! Tamanho
template <typename T> std::size_t BinaryTree<T>::size() const {
    return size_;
}

//! Pré ordem
template <typename T> ArrayList<T> BinaryTree<T>::pre_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->pre_order(v);
    return v;
}

//! Em ordem
template <typename T> ArrayList<T> BinaryTree<T>::in_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->in_order(v);
    return v;
}

//! Pós ordem
template <typename T> ArrayList<T> BinaryTree<T>::post_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->post_order(v);
    return v;
}

} // namespace structures

#endif