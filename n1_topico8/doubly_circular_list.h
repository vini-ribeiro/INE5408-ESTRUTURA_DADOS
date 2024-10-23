#include <stdexcept>

namespace structures {

template <typename T> class DoublyCircularList {
public:
  DoublyCircularList() : head(nullptr), size_(0) {}
  ~DoublyCircularList() { clear(); }

  void clear() {
    while (!empty())
      pop_back();
  }

  void push_back(const T &data) {
    Node *newNode = new Node(data);
    if (empty()) {
      newNode->next(newNode);
      newNode->prev(newNode);
      head = newNode;
      size_++;
      return;
    }
    newNode->next(head);
    newNode->prev(head->prev());
    head->prev(newNode);
    newNode->prev()->next(newNode);
    size_++;
  }
  void push_front(const T &data) {
    Node *newNode = new Node(data);
    if (empty()) {
      newNode->next(newNode);
      newNode->prev(newNode);
      head = newNode;
      size_++;
      return;
    }
    newNode->next(head);
    newNode->prev(head->prev());
    head->prev(newNode);
    newNode->prev()->next(newNode);
    head = newNode;
    size_++;
  }
  void insert(const T &data, std::size_t index) {
    if (index > size())
      throw std::out_of_range("Index inválida.");
    if (empty() || index == 0) {
      push_front(data);
      return;
    }
    if (index == size()) {
      push_back(data);
      return;
    }

    Node *ptrAux = head;
    for (size_t i = 0; i < index; ++i) {
      ptrAux = ptrAux->next();
    }

    Node *newNode = new Node(data);
    newNode->next(ptrAux);
    newNode->prev(ptrAux->prev());
    ptrAux->prev(newNode);
    newNode->prev()->next(newNode);
    size_++;
  }
  void insert_sorted(const T &data) {
    if (empty()) {
      push_back(data);
      return;
    }

    Node *ptrAux = head;
    for (size_t i = 0; i < size(); i++) {
      if (data < ptrAux->data()) {
        insert(data, i);
        return;
      }
      ptrAux = ptrAux->next();
    }
    push_back(data);
  }

  T pop(std::size_t index) {
    if (empty())
      throw std::out_of_range("Lista vazia.");
    if (index >= size())
      throw std::out_of_range("Index inválido.");
    if (index == 0)
      return pop_front();
    if (index == size() - 1)
      return pop_back();

    Node *ptrAux = head;
    for (size_t i = 0; i < index; ++i) {
      ptrAux = ptrAux->next();
    }
    T data = ptrAux->data();
    ptrAux->prev()->next(ptrAux->next());
    ptrAux->next()->prev(ptrAux->prev());
    delete ptrAux;
    size_--;
    return data;
  }
  T pop_back() {
    if (empty())
      throw std::out_of_range("Lista vazia.");
    Node *ptrAux = head->prev();
    T data = ptrAux->data();
    ptrAux->prev()->next(head);
    head->prev(ptrAux->prev());
    delete ptrAux;
    size_--;
    return data;
  }
  T pop_front() {
    if (empty())
      throw std::out_of_range("Lista vazia.");
    T data = head->data();
    remove(data);
    return data;
  }
  void remove(const T &data) {
    if (empty())
      throw std::out_of_range("Lista vazia.");
    if (!contains(data))
      return;

    if (size() == 1) {
      delete head;
      head = nullptr;
      size_--;
      return;
    }

    size_t index = find(data);
    Node *ptrAux = head;

    if (index == 0) {
      head = ptrAux->next();
      ptrAux->prev()->next(head);
      head->prev(ptrAux->prev());
      delete ptrAux;
      size_--;
      return;
    }

    for (size_t i = 0; i < index; i++) {
      ptrAux = ptrAux->next();
    }

    ptrAux->prev()->next(ptrAux->next());
    ptrAux->next()->prev(ptrAux->prev());
    delete ptrAux;
    size_--;
  }

  bool empty() const { return size() == 0; }
  bool contains(const T &data) const { return find(data) != size(); }

  T &at(std::size_t index) {
    if (index >= size())
      throw std::out_of_range("Index inválido.");

    Node *ptrAux = head;
    for (size_t i = 0; i < index; i++) {
      ptrAux = ptrAux->next();
    }
    return ptrAux->data();
  }
  const T &at(std::size_t index) const {
    if (index >= size())
      throw std::out_of_range("Index inválido.");

    Node *ptrAux = head;
    for (size_t i = 0; i < index; i++) {
      ptrAux = ptrAux->next();
    }
    return ptrAux->data();
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
  std::size_t size() const { return size_; }

private:
  class Node {
  public:
    explicit Node(const T &data)
        : data_(data), prev_(nullptr), next_(nullptr) {}
    Node(const T &data, Node *next)
        : data_(data), prev_(nullptr), next_(next) {}
    Node(const T &data, Node *prev, Node *next)
        : data_(data), prev_(prev), next_(next) {}

    T &data() { return data_; }
    const T &data() const { return data_; }

    Node *prev() { return prev_; }
    const Node *prev() const { return prev_; }

    void prev(Node *node) { prev_ = node; }

    Node *next() { return next_; }
    const Node *next() const { return next_; }

    void next(Node *node) { next_ = node; }

  private:
    T data_;
    Node *prev_;
    Node *next_;
  };

  Node *head;
  std::size_t size_;
};

}; // namespace structures