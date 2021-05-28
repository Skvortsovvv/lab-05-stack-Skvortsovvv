// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <memory>
#include <atomic>
#include <type_traits>
#include <utility>
#include <iostream>
#include <stdexcept>
template<typename T>
class Stack
{
private:
    Stack(Stack&) = delete;
    Stack& operator=(Stack&) = delete;

    static_assert(std::is_move_assignable<T>::value,
        "Error: this type is not moveable");
    static_assert(!std::is_copy_assignable<T>::value,
        "Error: type cant be copyable");
    static_assert(!std::is_copy_constructible<T>::value,
        "Error: type cant be copy construtible");

    struct node
    {
        node* next;
        //std::shared_ptr<T> data;
        T data;
        explicit node(T& d, node* n = nullptr):
            next(n), data(std::move(d)) {}
    };
    node* Head = nullptr;

public:
    Stack(){}
    ~Stack() {
        while (Head) {
            node* temp = Head;
            Head = Head->next;
            delete temp;
        }
    }
    template <typename ... Args>
    void push_emplace(Args&&... value) {
        T temp(std::forward<Args>(value)...);
        node* new_node = new node(temp, Head);
        Head = new_node;
    }

    void push(T&& value) {
        T temp(std::move(value));
        node* new_node = new node(
        temp, Head);
        Head = new_node;
    }

    const T& head() const {
        return Head->data;
        /*return *(Head->data);*/
    }
    T pop() {
        T Data = std::move(Head->data);
        node* to_be_delted = Head;
        Head = Head->next;
        delete to_be_delted;
        return Data;
        /*T Data = std::move(*(Head->data));
        node* to_be_deleted = Head;
        Head = Head->next;
        delete to_be_deleted;
        return Data;*/
    }
};
#endif // INCLUDE_HEADER_HPP_
