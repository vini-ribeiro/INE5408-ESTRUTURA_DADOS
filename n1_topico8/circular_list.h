#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstddef>
#include <cstdint>
#include <stdexcept>

namespace structures {

template <typename T> class CircularList {
  public:
    CircularList() : head(nullptr), tail(nullptr), size_(0) {
    }
    ~CircularList() {
        clear();
    }

    void clear() {
        while (!empty())
            pop_front();
    }

    void push_back(const T &data) {
        Node *newNode = new Node(data);

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
    void push_front(const T &data) {
        Node *newNode = new Node(data);

        if (empty()) {
            head = newNode;
            tail = newNode;
            size_++;
            return;
        }

        newNode->next(head);
        head = newNode;
        size_++;
    }
    void insert(const T &data, std::size_t index) {
        if (index > size())
            throw std::out_of_range("Index invalido");

        if (empty() || index == 0) {
            push_front(data);
            return;
        }

        if (index == size()) {
            push_back(data);
            return;
        }

        Node *ptrBefore = getNode(index - 1);
        Node *newNode = new Node(data, ptrBefore->next());
        ptrBefore->next(newNode);
        size_++;
    }
    void insert_sorted(const T &data) {
        if (empty()) {
            push_front(data);
            return;
        }

        Node *ptrAux = head;
        for (size_t i = 0; i < size(); i++) {
            if (ptrAux->data() > data) {
                insert(data, i);
                return;
            }
            ptrAux = ptrAux->next();
        }

        push_back(data);
    }

    T &at(std::size_t index) {
        if (empty())
            throw std::out_of_range("Lista vazia");
        if (index >= size())
            throw std::out_of_range("Index invalido");

        Node *ptr = getNode(index);
        return ptr->data();
    }
    const T &at(std::size_t index) const {
        if (empty())
            throw std::out_of_range("Lista vazia");
        if (index >= size())
            throw std::out_of_range("Index invalido");

        Node *ptr = head;
        for (size_t i = 0; i < index; i++) {
            ptr = ptr->next();
        }

        return ptr->data();
    }

    T pop(std::size_t index) {
        if (empty())
            throw std::out_of_range("Lista vazia");
        if (index >= size())
            throw std::out_of_range("Index invalido");

        if (index == 0)
            return pop_front();
        if (index == size() - 1)
            return pop_back();

        Node *ptrBefore = getNode(index - 1);
        Node *ptrToPop = ptrBefore->next();
        T data = ptrToPop->data();
        ptrBefore->next(ptrToPop->next());
        size_--;
        delete ptrToPop;
        return data;
    }
    T pop_back() {
        if (empty())
            throw std::out_of_range("Lista vazia");

        T data = tail->data();

        if (size() == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
            size_--;
            return data;
        }

        delete tail;
        tail = getNode(size() - 2);
        tail->next(nullptr);
        size_--;
        return data;
    }
    T pop_front() {
        if (empty())
            throw std::out_of_range("Lista vazia");

        T data = head->data();

        if (size() == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
            size_--;
            return data;
        }

        Node *ptrAux = head;
        head = head->next();
        delete ptrAux;
        size_--;
        return data;
    }
    void remove(const T &data) {
        if (empty())
            throw std::out_of_range("Lista vazia");
        if (!contains(data))
            return;

        size_t index = find(data);

        if (index == 0) {
            pop_front();
            return;
        }

        if (index == size() - 1) {
            pop_back();
            return;
        }

        Node *ptrBefore = getNode(index - 1);
        Node *ptrToRemove = ptrBefore->next();
        ptrBefore->next(ptrToRemove->next());
        delete ptrToRemove;
        size_--;
    }

    bool empty() const {
        return size() == 0;
    }
    bool contains(const T &data) const {
        return find(data) != size();
    }
    std::size_t find(const T &data) const {
        if (empty())
            return size();

        Node *ptrAux = head;
        for (size_t i = 0; i < size(); i++) {
            if (ptrAux->data() == data)
                return i;
            ptrAux = ptrAux->next();
        }

        return size();
    }

    std::size_t size() const {
        return size_;
    }

  private:
    class Node {
      public:
        explicit Node(const T &data) : data_(data), next_(nullptr) {
        }
        Node(const T &data, Node *next) : data_(data), next_(next) {
        }

        T &data() {
            return data_;
        }
        const T &data() const {
            return data_;
        }

        Node *next() {
            return next_;
        }
        const Node *next() const {
            return next_;
        }

        void next(Node *node) {
            next_ = node;
        }

      private:
        T data_;
        Node *next_;
    };

    Node *getNode(size_t index) {
        if (empty() || index >= size())
            return nullptr;

        Node *ptrAux = head;
        for (size_t i = 0; i < index; i++) {
            ptrAux = ptrAux->next();
        }

        return ptrAux;
    }

    Node *head;
    Node *tail;
    size_t size_;
};

} // namespace structures

#endif
