// Copyright [2024] VINICIUS HENRIQUE RIBEIRO

#include <cstddef>

#include "array_list.h"

namespace structures {

template <typename T>
class AVLTree {
   public:
    AVLTree() : root(nullptr), size_(0) {}
    ~AVLTree() { delete root; }

    void insert(const T &data);

    void remove(const T &data);

    bool contains(const T &data) const;

    bool empty() const;

    std::size_t size() const;

    int height() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

   private:
    struct Node {
        Node(const T &data)
            : data_(data), height_(0), left_(nullptr), right_(nullptr) {}

        ~Node() {
            delete left_;
            delete right_;
        }

        T data_;
        int height_;
        Node *left_;
        Node *right_;

        Node *insert(const T &data) {
            // se dado for menor, isere à esquerda
            if (data_ > data) {
                // se não tiver nodo à esquerda, cria
                if (left_ == nullptr) {
                    left_ = new Node(data);
                } else {
                    // se tiver nodo à esquerda, delega a inserção ao filho à
                    // esquerda
                    left_ = left_->insert(data);
                }
            } else {
                // se dado for menor ou igual, isere à direita
                // se não tiver nodo à direita, cria
                if (right_ == nullptr) {
                    right_ = new Node(data);
                } else {
                    // se tiver nodo à direita, delega a inserção ao filho à
                    // direta
                    right_ = right_->insert(data);
                }
            }

            updateHeight();
            return balance();
        }

        Node *balance() {
            if (height_difference() >= 2) {
                // LR é dupla para a direita
                if (left_->height_difference() < 0) {
                    left_ = left_->simpleLeft();
                }
                return simpleRight();
            }

            // rotaciona para esquerda
            if (height_difference() <= -2) {
                // RL é dupla para a esquerda
                if (right_->height_difference() > 0) {
                    right_ = right_->simpleRight();
                }
                return simpleLeft();
            }

            return this;
        }

        Node *remove(Node *node, const T &data) {
            if (node == nullptr) return node;

            if (node->data_ > data) {
                node->left_ = remove(node->left_, data);
                node->updateHeight();
                return node->balance();
            }

            if (node->data_ < data) {
                node->right_ = remove(node->right_, data);
                node->updateHeight();
                return node->balance();
            }

            if (node->left_ != nullptr && node->right_ != nullptr) {
                Node *minimum = node->right_->getMinimum();
                node->data_   = minimum->data_;
                node->right_  = remove(node->right_, node->data_);
                node->updateHeight();
                return node->balance();
            }

            if (node->left_ != nullptr) {
                Node *aux   = node->left_;
                node->left_ = nullptr;
                delete node;
                return aux;
            }

            if (node->right_ != nullptr) {
                Node *aux    = node->right_;
                node->right_ = nullptr;
                delete node;
                return aux;
            }

            delete node;
            return nullptr;
        }

        bool contains(const T &data) const {
            const Node *aux = this;

            while (aux != nullptr) {
                if (aux->data_ > data)
                    aux = aux->left_;
                else if (aux->data_ < data)
                    aux = aux->right_;
                else
                    return true;
            }

            return false;
        }

        int height_difference() const {
            int hl, hr;
            if (left_ == nullptr)
                hl = -1;
            else
                hl = left_->height_;

            if (right_ == nullptr)
                hr = -1;
            else
                hr = right_->height_;

            return hl - hr;
        }

        void updateHeight() {
            int hl = (left_ == nullptr) ? -1 : left_->height_;
            int hr = (right_ == nullptr) ? -1 : right_->height_;

            height_ = (hl > hr) ? hl + 1 : hr + 1;
        }

        Node *simpleLeft() {
            Node *aux  = right_;
            right_     = aux->left_;
            aux->left_ = this;
            updateHeight();
            aux->updateHeight();
            return aux;
        }

        Node *simpleRight() {
            Node *aux   = left_;
            left_       = aux->right_;
            aux->right_ = this;
            updateHeight();
            aux->updateHeight();
            return aux;
        }

        void pre_order(ArrayList<T> &v) const {
            v.push_back(this->data_);
            if (this->left_ != nullptr) this->left_->pre_order(v);
            if (this->right_ != nullptr) this->right_->pre_order(v);
        }

        void in_order(ArrayList<T> &v) const {
            if (this->left_ != nullptr) this->left_->in_order(v);
            v.push_back(this->data_);
            if (this->right_ != nullptr) this->right_->in_order(v);
        }

        void post_order(ArrayList<T> &v) const {
            if (this->left_ != nullptr) this->left_->post_order(v);
            if (this->right_ != nullptr) this->right_->post_order(v);
            v.push_back(this->data_);
        }

        int height() { return height_; }

        Node *getMinimum() {
            if (this->left_ == nullptr) return this;
            return this->left_->getMinimum();
        }

        Node *getMaximum() {
            if (this->right_ == nullptr) return this;
            return this->right_->getMaximum();
        }
    };

    Node *root;
    std::size_t size_;
};

}  // namespace structures

// -----

template <typename T>
void structures::AVLTree<T>::insert(const T &data) {
    if (empty()) {
        root = new Node(data);
        size_++;
    } else {
        root = root->insert(data);
        root->updateHeight();
        size_++;
    }
}

template <typename T>
void structures::AVLTree<T>::remove(const T &data) {
    if (!empty() && contains(data)) {
        root = root->remove(root, data);
        size_--;
    }
}

template <typename T>
bool structures::AVLTree<T>::contains(const T &data) const {
    if (empty()) return false;
    return root->contains(data);
}
template <typename T>
bool structures::AVLTree<T>::empty() const {
    return root == nullptr;
}

template <typename T>
std::size_t structures::AVLTree<T>::size() const {
    return size_;
}

template <typename T>
int structures::AVLTree<T>::height() const {
    if (root == nullptr) return -1;
    return root->height_;
}

template <typename T>
structures::ArrayList<T> structures::AVLTree<T>::pre_order() const {
    ArrayList<T> v;
    if (root != nullptr) root->pre_order(v);
    return v;
}

template <typename T>
structures::ArrayList<T> structures::AVLTree<T>::in_order() const {
    ArrayList<T> v;
    if (root != nullptr) root->in_order(v);
    return v;
}

template <typename T>
structures::ArrayList<T> structures::AVLTree<T>::post_order() const {
    ArrayList<T> v;
    if (root != nullptr) root->post_order(v);
    return v;
}