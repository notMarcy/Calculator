#ifndef MY_CONTAINERS_HPP
#define MY_CONTAINERS_HPP

#include <stdexcept>
#include <cstddef>


template <typename T>
class MyStack {
private:
    struct Node {
        T data;
        Node* next;
        Node(T value, Node* nextNode) : data(value), next(nextNode) {}
    };

    Node* topNode = nullptr;
    size_t _size = 0;

public:
    MyStack() : topNode(nullptr), _size(0) {}

    ~MyStack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(T value) {
        topNode = new Node(value, topNode);
        _size++;
    }

    void pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack underflow: cannot pop from empty stack");
        }
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        _size--;
    }

    T top() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        return topNode->data;
    }

    bool isEmpty() const { return topNode == nullptr; }
    size_t size() const { return _size; }
};

template <typename T>
class MyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node* head = nullptr;
    size_t _size = 0;

public:
    MyLinkedList() : head(nullptr), _size(0) {}

    ~MyLinkedList() {
        clear();
    }

    /** @brief Вставка в конец списка */
    void insert(T value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        _size++;
    }

    T get(int index) const {
        if (index < 0 || index >= static_cast<int>(_size)) {
            throw std::out_of_range("Index out of bounds");
        }
        Node* temp = head;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        return temp->data;
    }

    void remove(T value) {
        Node* curr = head;
        Node* prev = nullptr;

        while (curr) {
            if (curr->data == value) {
                if (prev) {
                    prev->next = curr->next;
                } else {
                    head = curr->next;
                }
                delete curr;
                _size--;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        _size = 0;
    }

    bool isEmpty() const { return _size == 0; }
    size_t size() const { return _size; }
};

#endif 