// Copyright 2024 Vinicius Henrique Ribeiro

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
class LinkedQueue {
 public:
    LinkedQueue() : head(nullptr), tail(nullptr), size_(0) {}

    ~LinkedQueue() {
        clear();
    }

    // limpar
    void clear() {
        while (!empty()) {
        dequeue();
        }
    }

    // enfilerar
    void enqueue(const T& data) {
        Node *newNode = new Node(data, nullptr);
        if (empty()) {
            head = newNode;
            tail = newNode;
            size_++;
            return;
        }

        tail->next(newNode);
        tail = newNode;
        size_++;
    }

    // desenfilerar
    T dequeue() {
        if (empty()) throw std::out_of_range("Fila vazia");

        T aux = head->data();

        if (size() == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
            size_--;
            return aux;
        }

        Node *ptrAux = head;
        head = head->next();
        delete ptrAux;
        size_--;
        return aux;
    }

    // primeiro dado
    T& front() const {
        if (empty()) throw std::out_of_range("Fila vazia");
        return head->data();
    }

    // último dado
    T& back() const {
        if (empty()) throw std::out_of_range("Fila vazia");
        return tail->data();
    }

    // fila vazia
    bool empty() const {return size() == 0;}

    // tamanho
    std::size_t size() const {return size_;}

 private:
    class Node {
     public:
        explicit Node(const T& data) : data_(data), next_(nullptr) {}
        Node(const T& data, Node* next): data_(data), next_(next) {}
        // getter: info
        T& data() {return data_;}
        // getter-constante: info
        const T& data() const {return data_;}
        // getter: próximo
        Node* next() {return next_;}
        // getter-constante: próximo
        const Node* next() const {return next_;}
        // setter: próximo
        void next(Node* next) {next_ = next;}
     private:
        T data_;
        Node* next_;
    };
    Node* head;  // nodo-cabeça
    Node* tail;  // nodo-fim
    std::size_t size_;  // tamanho
};
}  // namespace structures
