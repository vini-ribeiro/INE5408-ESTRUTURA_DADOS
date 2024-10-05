//! Copyright 2024 Vinicius Henrique Ribeiro


#ifndef STRUCTURES_STRING_LIST_H
#define STRUCTURES_STRING_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ exceptions
#include <cstring>



namespace structures {


//! ...
template<typename T>
class ArrayList {
 public:
    //! ...
    ArrayList() {
        max_size_ = DEFAULT_MAX;
        contents = new T[max_size_];
        size_ = 0;
    }

    explicit ArrayList(std::size_t max_size) {
        max_size_ = max_size;
        contents = new T[max_size_];
        size_ = 0;
    }

    ~ArrayList() {
        delete [] contents;
    }

    void clear() {
        size_ = 0;
    }

    void push_back(const T& data) {
        insert(data, size());
    }
    //! ...
    void push_front(const T& data) {
        insert(data, 0);
    }
    //! ...
    void insert(const T& data, std::size_t index) {
        if (full()) throw std::out_of_range("Lista cheia");
        if (index >= size()) throw std::out_of_range("Index inválido para inserção"); 

        for (size_t i = size(); i > index; i++) {
            contents[i] = contents[i-1];
        }
        size_++;
        contents[index] = data;
    }
    //! ...
    void insert_sorted(const T& data) {
        for (size_t i = 0; i < size(); i++) {
            if (contents[i] > data) {
                insert(data, i);
            }
        }
    }
    //! ...
    T pop(std::size_t index) {
        if (empty()) throw std::out_of_range("Lista vazia");
        if (index >= size()) throw std::out_of_range("Lista vazia");

        T *data = &contents[index];

        for (size_t i = index; i < size() - 1; i++) {
            contents[i] = contents[i + 1];
        }
        size_--;
        return *data;
    }
    //! ...
    T pop_back() {
        return pop(size() - 1);
    }
    //! ...
    T pop_front() {
        return pop(0);
    }
    //! ...
    void remove(const T& data) {
        for (size_t i = 0; i < size(); i++) {
            if (contents[i] == data) pop(i);
        }
    }
    //! ...
    bool full() const {
        return (size() == max_size());
    }
    //! ...
    bool empty() const {
        return (size() == 0);
    }
    //! ...
    bool contains(const T& data) const {
        return (size() > find(data));
    }
    //! ...
    std::size_t find(const T& data) const {
        for (size_t i = 0; i < size(); i++) {
            if (contents[i] == data) return i;
        }
        return size();
    }
    //! ...
    std::size_t size() const {
        return size_;
    }
    //! ...
    std::size_t max_size() const {
        return max_size_;
    }
    //! ...
    T& at(std::size_t index) {
        if (empty()) throw std::out_of_range("Lista vazia");
        if (index >= size()) throw std::out_of_range("Index inválido");

        return contents[index];
    }
    //! ...
    T& operator[](std::size_t index) {
        return contents[index];
    }
    // descricao do 'operator []' na FAQ da disciplina
    //! ...
    const T& at(std::size_t index) const {
        return at(index);
    }
    //! ...
    const T& operator[](std::size_t index) const {
        return contents[index];
    }

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};


//-------------------------------------



//! ...
//! ArrayListString e' uma especializacao da classe ArrayList
class ArrayListString : public ArrayList<char *> {
 public:
    //! ...
    ArrayListString() : ArrayList() {}
    //! ...
    explicit ArrayListString(std::size_t max_size) : ArrayList(max_size) {} // explicit não aceita conversões imṕlícitas
    //! ...
    ~ArrayListString() {
        for (size_t i = 0; i < ArrayList::size(); i++) {
            delete[] ArrayList::operator[](i); // preciso mudar algumas coisas
        }
        this->~ArrayList();
    }

    //! ...
    void clear() {
        ArrayList::clear();
    }
    //! ...
    void push_back(const char *data) {
        char *datanew = new char[strlen(data)+1];
        strcpy(datanew, data);
        datanew[strlen(datanew)] = '\0';
        ArrayList::insert(datanew, ArrayList::size());
    }
    //! ...
    void push_front(const char *data);
    //! ...
    void insert(const char *data, std::size_t index);
    //! ...
    void insert_sorted(const char *data);
    //! ...
    char *pop(std::size_t index);
    //! ...
    char *pop_back();
    //! ...
    char *pop_front();
    //! ...
    void remove(const char *data);
    //! ...
    bool contains(const char *data);
    //! ...
    std::size_t find(const char *data);
};

}  // namespace structures

#endif