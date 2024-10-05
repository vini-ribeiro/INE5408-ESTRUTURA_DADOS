//! Copyright 2024 Vinicius Henrique Ribeiro

#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

//! ...
template<typename T>
class LinkedList {
 public:
    //! ...
    LinkedList();  // construtor padrão
    //! ...
    ~LinkedList();  // destrutor
    //! ...
    void clear();  // limpar lista
    //! ...
    void push_back(const T& data);  // inserir no fim
    //! ...
    void push_front(const T& data);  // inserir no início
    //! ...
    void insert(const T& data, std::size_t index);  // inserir na posição
    //! ...
    void insert_sorted(const T& data);  // inserir em ordem
    //! ...
    T& at(std::size_t index);  // acessar um elemento na posição index
    //! ...
    T pop(std::size_t index);  // retirar da posição
    //! ...
    T pop_back();  // retirar do fim
    //! ...
    T pop_front();  // retirar do início
    //! ...
    void remove(const T& data);  // remover específico
    //! ...
    bool empty() const;  // lista vazia
    //! ...
    bool contains(const T& data) const;  // contém
    //! ...
    std::size_t find(const T& data) const;  // posição do dado
    //! ...
    std::size_t size() const;  // tamanho da lista

 private:
    class Node {  // Elemento (implementação pronta)
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* before_index(std::size_t index) {  // nó anterior ao 'index'
        auto it = head;
        for (auto i = 1u; i < index; ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    Node* tail{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif


//! Construtor
template<typename T>
structures::LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
    size_ = 0u;
}

//! Destrutor
template<typename T>
structures::LinkedList<T>::~LinkedList() {
    clear();
}

//! Esvazia
template<typename T>
void structures::LinkedList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

//! Inserção no início
template<typename T>
void structures::LinkedList<T>::push_front(const T& data) {
    Node *novo;
    novo = new Node(data, head);
    if (novo == nullptr) {
        throw std::out_of_range("memória insuficiente");
    }
    if (head == nullptr) {
        tail = novo;
    }
    head = novo;
    size_++;
}

//! Inserção no fim
template<typename T>
void structures::LinkedList<T>::push_back(const T& data) {
    Node *novo;
    if (empty()) {
        return push_front(data);
    }
    novo = new Node(data, nullptr);
    if (novo == nullptr) {
        throw std::out_of_range("memória insuficiente");
    }
    tail->next(novo);
    tail = novo;
    size_++;
}

//! Dado da posição 'index'
template<typename T>
T& structures::LinkedList<T>::at(std::size_t index) {
    if (index >= size()) throw std::out_of_range("Index inválido");

    Node *ptrAux = head;
    for (std::size_t i = 0; i < index; i++) 
        ptrAux = ptrAux->next();

    return ptrAux->data();
}

//! Inserção na posição 'index'
template<typename T>
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {
    if (index > size()) throw std::out_of_range("Index inválido");

    if (index == 0) {
        push_front(data);
        return;
    }
    if (index == size()) {
        push_back(data);
        return;
    }

    Node *newNode = new Node(data);
    Node *ptrAux = head;
    for (std::size_t i = 0; i < index - 1; i++) 
        ptrAux = ptrAux->next();

    newNode->next(ptrAux->next());
    ptrAux->next(newNode);
    size_++;
}

//! Inserção ordenada
template<typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_front(data);
        return;
    }

    if (tail->data() < data) {
        push_back(data);
        return;
    }

    if (head->data() > data) {
        push_front(data);
        return;
    }

    Node *ptrAux = head;
    std::size_t index = 0;
    while (ptrAux != nullptr) {
        if (ptrAux->data() > data) {
            insert(data, index);
            return;
        }
        ptrAux = ptrAux->next();
        index++;
    }
}

//! Remoção do início
template<typename T>
T structures::LinkedList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    T aux;
    Node *p;
    p = head;
    head = p->next();
    aux = p->data();
    delete p;
    if (head == nullptr) {
        tail = nullptr;
    }
    size_--;
    return aux;
}

//! Remoção do fim
template<typename T>
T structures::LinkedList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    }
    if (size() == 1) {
        return pop_front();
    }
    T aux;
    Node *p, *ant;
    ant = nullptr;
    p = head;
    while (p != tail) {  // 'ant' deve apontar para o penúltimo nó
        ant = p;
        p = p->next();
    }
    aux = p->data();
    delete p;
    if (ant == nullptr) {
        head = nullptr;
    } else {
        ant->next(nullptr);
    }
    tail = ant;
    size_--;
    return aux;
}

//! Remoção da posição 'index'
template<typename T>
T structures::LinkedList<T>::pop(std::size_t index) {
    if (empty() || index >= size()) throw std::out_of_range("Lista vazia");
    if (index == 0) return pop_front();
    if (index == size() - 1) return pop_back();

    Node *ptrAux = head;
    for (std::size_t i = 0; i < index - 1; i++) {
        ptrAux = ptrAux->next();
    }

    Node *ptrPop = ptrAux->next();
    T aux = ptrPop->data();
    ptrAux->next(ptrPop->next());
    delete ptrPop;
    size_--;
    return aux;
}

//! Remoção de um dado
template<typename T>
void structures::LinkedList<T>::remove(const T& data) {
    pop(find(data));
}

//! Verificação de vazia
template<typename T>
bool structures::LinkedList<T>::empty() const {
    return size() == 0u;
}

//! Verificação se contém um dado
template<typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
    return find(data) != size();
}

//! Índice de um dado (se existir); ou 'size() (se não existir)
template<typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
    if (empty()) return size();

    Node *ptrAux;
    ptrAux = head;
    std::size_t index = 0;
    while (ptrAux != nullptr) {
        if (ptrAux->data() == data) return index;
        index++;
        ptrAux = ptrAux->next();
    }

    return size();
}

//! Quantidade atual de elementos
template<typename T>
std::size_t structures::LinkedList<T>::size() const {
    return size_;
}
