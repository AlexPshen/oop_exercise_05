#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <iterator>
#include <memory>
#include <array>
#include <iostream>
#include<string.h>

template<class T>
struct que{
private:
    struct que_el;
    std::shared_ptr<que_el> front = nullptr;
    std::shared_ptr<que_el> back = nullptr;
    //que() = default;
    //que(const que&) = delete;
    que &operator = (const que &) = delete;
    size_t size = 0;
public:
    void push(T value);
    void pop();
    T& top();
    struct forward_it{
        using value_type = T;
        using reference = T &;
        using pointer = T *;
        using difference_type = ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        forward_it(que_el *el) : ptr(el) {};

        T& operator* ();
        forward_it& operator++ ();
        forward_it operator++ (int r);
        forward_it next_it();

        bool operator== (const forward_it& it) const;
        bool operator!= (const forward_it& it) const; 
       
    //private:
        que_el* ptr;

        friend class que;
    };

    forward_it begin();
    forward_it end();
    void insert(int &ind, const T &val);
    void insert_it(const forward_it& it, const T& value);
    void erase(const forward_it& it); 
private:
    struct que_el{
        T value;
        std::shared_ptr<que_el> tail = nullptr;
        forward_it next_it();
        
        que_el(const T& value, std::shared_ptr<que_el> next) : value(value), tail(next) {};
    };
};

template<class T>
void que<T>::insert(int &ind, const T &val){
    int i = ind - 1;
    try{
        if(i == -1){
            if(size == 0){
                this -> push(val);
                return;
            }
            std::shared_ptr<que_el> p(new que_el{val, nullptr});
            p -> tail = front;
            front = p;
            return;
        } else if(i < -1 || i > this -> size){
            throw "Неверный индекс";
        } else {
            auto it = this -> begin();
            for(int j = 0; j < i; ++j){
                ++it;
            }
            this -> insert_it(it, val);
        }
    }
    catch(const char* str){
        std::cout << str << '\n';
        return;
    }
}
    
           

template<class T>
void que<T>::insert_it(const que<T>::forward_it &it, const T &value) {
    std::shared_ptr<que_el> p(new que_el{value, nullptr});
    try{
        if(it.ptr == nullptr && size != 0){
            throw "индекс неверный";
        }
        if(it.ptr == back.get()){
            this -> push(value);
            return;
        }
        p -> tail = it.ptr -> tail;
        it.ptr -> tail = p;
        ++ size;
    } catch(const char* str){
        std::cout << str << '\n';
        return;
    }
}

template<class T>
void que<T>::erase(const que<T>::forward_it &it) {
    try{
        if (it.ptr == nullptr) {
            throw "Нельзя удалить";
        }
        if(it == this -> begin()){
            if(front == back){
                this -> pop();
                return;
            }
            front = front -> tail;
        } else {
            auto tmp = this -> begin();
            while(tmp.ptr -> next_it() != it.ptr){
                ++ tmp;
            }
            tmp.ptr -> tail = it.ptr -> tail;
        }
    }
    catch(const char* str){
        std::cout << str << "\n";
    }
}


template<class T>
typename que<T>::forward_it que<T>::begin() {
    return front.get();
}

template<class T>
typename que<T>::forward_it que<T>::end() {
    return nullptr;
}

template<class T>
typename que<T>::forward_it que<T>::que_el::next_it() {
    return tail.get();
}

template<class T>
T &que<T>::forward_it::operator*() {
    return ptr -> value;
}

template<class T>
typename que<T>::forward_it &que<T>::forward_it::operator++() {
    *this = ptr -> next_it();
    return *this;
}

template<class T>
typename que<T>::forward_it que<T>::forward_it::operator++(int) {
    forward_it old = *this;
    ++*this;
    return old;
}

template<class T>
bool que<T>::forward_it::operator==(const forward_it &it) const{
    return ptr == it.ptr;
}

template<class T>
bool que<T>::forward_it::operator!=(const forward_it &it) const{
    return ptr != it.ptr;
}

template<class T>
void que<T>::push(T value){
    std::shared_ptr<que_el> p(new que_el{value, nullptr});
    try{
        if(p == nullptr){
            throw "Новый элемент не вставился";
        }
        p -> tail = nullptr;
        ++ size;
        if(back == nullptr){
            front = p;
            back = p;
            return;
        }
        back -> tail = p;
        back = p;
    }
    catch(char* str){
        std::cout << str << "\n";
    }
}

template<class T>
void que<T>::pop(){
    try{
        if(front == nullptr){
            throw "Очередь пуста";
        }
        std::shared_ptr<que_el> p = front;
        front = front -> tail;
        -- size;
        if(front == nullptr){
            back = nullptr;
            return;
        }
    }
    catch(const char* str){
        std::cout << str << "\n";
        return;
    }
}

template<class T>
T& que<T>::top(){
    try{
        if(front == nullptr){
            throw "Очередь пуста";
        }
        return front -> value;
    }
    catch(const char* str){
        std::cout << str << "\n";
    }
}


#endif

