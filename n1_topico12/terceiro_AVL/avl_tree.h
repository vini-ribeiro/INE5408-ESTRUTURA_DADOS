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
        Node(const T &data) : data_(data), height_(0), left_(nullptr), right_(nullptr) {}

        ~Node() {
            delete left_;
            delete right_;
        }

        T data_;
        int height_;
        Node *left_;
        Node *right_;

        void insert(const T &data) {
            Node *aux = this;

            while (aux != nullptr) {
                if (aux->data_ > data) {
                    if (aux->left_ == nullptr) {
                        aux->left_ = new Node(data);
                        aux->left_->height_ = aux->height_ + 1;
                        break;
                    }
                    aux = aux->left_;
                } else {
                    if (aux->right_ == nullptr) {
                        aux->right_ = new Node(data);
                        aux->right_->height_ = aux->height_ + 1;
                        break;
                    }
                    aux = aux->right_;
                }
            }
        }

        Node *remove(Node *node, const T &data) {
            if (node == nullptr)
                return node;

            if (node->data_ > data) {
                node->left_ = remove(node->left_, data);
                return node;
            }

            if (node->data_ < data) {
                node->right_ = remove(node->right_, data);
                return node;
            }

            if (node->left_ != nullptr && node->right_ != nullptr) {
                Node *minimum = node->right_->getMinimum();
                node->data_ = minimum->data_;
                node->right_ = remove(node->right_, node->data_);
                return node;
            }

            if (node->left_ != nullptr) {
                Node *aux = node->left_;
                node->left_ = nullptr;
                delete node;
                return aux;
            }

            if (node->right_ != nullptr) {
                Node *aux = node->right_;
                node->right_ = nullptr;
                delete node;
                return aux;
            }

            delete node;
            return nullptr;
        }

        bool contains(const T &data) const {
            Node *aux = this;

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

        void updateHeight();

        Node *simpleLeft();

        Node *simpleRight();

        Node *doubleLeft();

        Node *doubleRight();

        void pre_order(ArrayList<T> &v) const {
            v.push_back(this->data_);
            if (this->left_ != nullptr)
                this->left_->pre_order(v);
            if (this->right_ != nullptr)
                this->right_->pre_order(v);
        }

        void in_order(ArrayList<T> &v) const {
            if (this->left_ != nullptr)
                this->left_->in_order(v);
            v.push_back(this->data_);
            if (this->right_ != nullptr)
                this->right_->in_order(v);
        }

        void post_order(ArrayList<T> &v) const {
            if (this->left_ != nullptr)
                this->left_->post_order(v);
            if (this->right_ != nullptr)
                this->right_->post_order(v);
            v.push_back(this->data_);
        }

        int height() { return height_; }

        Node *getMinimum() {
            if (this->left_ == nullptr)
                return this;
            return this->left_->getMinimum();
        }

        Node *getMaximum() {
            if (this->right_ == nullptr)
                return this;
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
    if (root == nullptr) {
        root = new Node(data);
        size_++;
    } else {
        root->insert(data);
        size_++;
    }
}

template <typename T>
bool structures::AVLTree<T>::contains(const T &data) const {
    if (root == nullptr)
        return false;
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
    return root->height();
}

template <typename T>
structures::ArrayList<T> structures::AVLTree<T>::pre_order() const {
    ArrayList<T> v;
    root->pre_order(v);
    return v;
}

template <typename T>
structures::ArrayList<T> structures::AVLTree<T>::in_order() const {
    ArrayList<T> v;
    root->in_order(v);
    return v;
}

template <typename T>
structures::ArrayList<T> structures::AVLTree<T>::post_order() const {
    ArrayList<T> v;
    root->post_order(v);
    return v;
}