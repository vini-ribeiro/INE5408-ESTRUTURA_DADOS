// Copyright 2024 Vinicius Henrique Ribeiro

#include <cstdint>
#include <stdexcept>


namespace structures {

template<typename T>
class LinkedStack {
public:
    LinkedStack()
    : top_(nullptr), size_(0) {}

    ~LinkedStack() {clear();}

    void clear() {while (!empty()) pop();} // limpa pilha

    // empilha
    void push(const T& data) {
        Node *newNode = new Node(data, top_);
        top_ = newNode;
        size_++;
    }

    // desempilha
    T pop() {
        if (empty()) throw std::out_of_range("Pilha vazia");
        Node *ptrAux = top_;
        top_ = top_->next();
        T aux = ptrAux->data();
        delete ptrAux;
        size_--;
        return aux;
    }

    // dado no topo
    T& top() const {
        if (empty()) throw std::out_of_range("Pilha vazia");
        return top_->data();
    } 

    bool empty() const {return size_ == 0;} // pilha vazia

    std::size_t size() const {return size_;} // tamanho da pilha

private:
    class Node {
    public:
        Node(const T& data) : data_(data), next_(nullptr) {}
        Node(const T& data, Node* next): data_(data), next_(next) {}

        T& data() {return data_;} // getter: info
        const T& data() const {return data_;} // getter-constante: info

        Node* next() {return next_;} // getter: próximo
        const Node* next() const {return next_;} // getter-constante: próximo

        void next(Node* next) {next_ = next;} // setter: próximo
    private:
        T data_;
        Node* next_;
    };

        Node* top_; // nodo-topo
        std::size_t size_; // tamanho
    };

}