#ifndef Deque_h
#define Deque_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#define initial_size 2
#define Deque_DEFINE(T) \
typedef struct Deque_##T Deque_##T; \
typedef struct Deque_##T##_Iterator Deque_##T##_Iterator; \
struct Deque_##T { \
    T* arr; \
    int front_index; \
    int back_index; \
    int arr_length; \
    int max_length; \
    char type_name[strlen("Deque_"#T)+1]; \
    size_t (*size)(const Deque_##T* ); \
    bool (*empty)(const Deque_##T* ); \
    void (*push_front)(Deque_##T* , const T &); \
    void (*push_back)(Deque_##T* , const T &); \
    const T& (*front)(const Deque_##T* ); \
    const T& (*back)(const Deque_##T* ); \
    void (*pop_front)(Deque_##T* ); \
    void (*pop_back)(Deque_##T* ); \
    Deque_##T##_Iterator (*begin)(const Deque_##T* ); \
    Deque_##T##_Iterator (*end)(const Deque_##T* ); \
    const T& (*at)(const Deque_##T* , size_t i); \
    void (*dtor)(Deque_##T* ); \
    void (*clear)(Deque_##T* ); \
    bool (*less)(const T &, const T &); \
}; \
struct Deque_##T##_Iterator { \
    int index; \
    int length; \
    int begin_index; \
    T* arr_iterator; \
    void (*inc)(Deque_##T##_Iterator* ); \
    void (*dec)(Deque_##T##_Iterator* ); \
    const T& (*deref)(const Deque_##T##_Iterator* ); \
}; \
size_t Deque_size(const Deque_##T* deque) { \
    return deque->arr_length; \
} \
bool Deque_empty(const Deque_##T* deque) { \
    return (deque->arr_length==0); \
} \
void Deque_push_front(Deque_##T* deque, const T & input) { \
    if (deque->arr_length == deque->max_length) \
    { \
        deque->max_length = std::max(2*(deque->max_length), initial_size); \
        T* temp = (T*)malloc(sizeof(T)*(deque->max_length)); \
        for (int i=0; i<deque->arr_length; i++) \
            temp[i+1] = deque->arr[(i+deque->front_index)%deque->arr_length]; \
        temp[0] = input; \
        if (deque->arr!=NULL) free(deque->arr); \
        deque->arr = temp; \
        deque->front_index = 0; \
        deque->back_index = deque->arr_length; \
    } \
    else \
    { \
        deque->front_index = (deque->front_index - 1 + deque->max_length)%deque->max_length; \
        deque->arr[deque->front_index] = input; \
    } \
    deque->arr_length ++; \
} \
void Deque_push_back(Deque_##T* deque, const T & input) { \
    if (deque->arr_length == deque->max_length) \
    { \
        deque->max_length = std::max(2*(deque->max_length), initial_size); \
        T* temp = (T*)malloc(sizeof(T)*(deque->max_length)); \
        for (int i=0; i<deque->arr_length; i++) \
            temp[i] = deque->arr[(i+deque->front_index)%deque->arr_length]; \
        temp[deque->arr_length] = input; \
        if (deque->arr!=NULL) free(deque->arr); \
        deque->arr = temp; \
        deque->front_index = 0; \
        deque->back_index = deque->arr_length; \
    } \
    else \
    { \
        deque->back_index = (deque->back_index + 1)%deque->max_length; \
        deque->arr[deque->back_index] = input; \
    } \
    deque->arr_length ++; \
} \
const T& Deque_front(const Deque_##T* deque) { \
    if (deque->arr_length == 0) \
        exit(-1); \
    return deque->arr[deque->front_index]; \
} \
const T& Deque_back(const Deque_##T* deque) { \
    if (deque->arr_length == 0) \
        exit(-1); \
    return deque->arr[deque->back_index]; \
} \
void Deque_pop_front(Deque_##T* deque) { \
    if (deque->arr_length == 0) exit(-1); \
    deque->front_index = (deque->front_index + 1)%deque->max_length; \
    deque->arr_length --; \
} \
void Deque_pop_back(Deque_##T* deque) { \
    if (deque->arr_length == 0) exit(-1); \
    deque->back_index = (deque->back_index - 1 + deque->max_length)%deque->max_length; \
    deque->arr_length --; \
} \
void Iterator_inc(Deque_##T##_Iterator* it) { \
    it->index ++; \
} \
void Iterator_dec(Deque_##T##_Iterator* it) { \
    it->index --; \
} \
const T& Iterator_deref(const Deque_##T##_Iterator* it) { \
    return it->arr_iterator[(it->index + it->begin_index)%it->length]; \
} \
Deque_##T##_Iterator Deque_begin(const Deque_##T* deque) { \
    Deque_##T##_Iterator temp; \
    temp.index = 0; \
    temp.begin_index = deque->front_index; \
    temp.length = deque->max_length; \
    temp.arr_iterator = deque->arr; \
    temp.inc = Iterator_inc; \
    temp.dec = Iterator_dec; \
    temp.deref = Iterator_deref; \
    return temp; \
} \
Deque_##T##_Iterator Deque_end(const Deque_##T* deque) { \
    Deque_##T##_Iterator temp; \
    temp.index = deque->arr_length; \
    temp.begin_index = deque->front_index; \
    temp.length = deque->max_length; \
    temp.arr_iterator = deque->arr; \
    temp.inc = Iterator_inc; \
    temp.dec = Iterator_dec; \
    temp.deref = Iterator_deref; \
    return temp; \
}\
const T& Deque_at(const Deque_##T* deque, size_t i) { \
    return deque->arr[(i + deque->front_index + deque->max_length)%deque->max_length]; \
} \
void Deque_clear(Deque_##T* deque) { \
    deque->arr_length = 0; \
    deque->max_length = 0; \
} \
void Deque_dtor(Deque_##T* deque) { \
    if (deque->arr != NULL) free(deque->arr); \
} \
void Deque_##T##_ctor(Deque_##T* deque, bool (*Deque_less)(const T &, const T &)) { \
    deque->arr = NULL; \
    deque->front_index = 0; \
    deque->back_index = 0; \
    deque->arr_length = 0; \
    deque->max_length = 0; \
    const char temp_name[] = "Deque_"#T; \
    for (size_t i=0; i<=strlen(temp_name); i++) \
        deque->type_name[i] = temp_name[i]; \
    deque->size = Deque_size; \
    deque->empty = Deque_empty; \
    deque->push_front = Deque_push_front; \
    deque->push_back = Deque_push_back; \
    deque->front = Deque_front; \
    deque->back = Deque_back; \
    deque->pop_front = Deque_pop_front; \
    deque->pop_back = Deque_pop_back; \
    deque->begin = Deque_begin; \
    deque->end = Deque_end; \
    deque->at = Deque_at; \
    deque->clear = Deque_clear; \
    deque->dtor = Deque_dtor; \
    deque->less = Deque_less; \
} \
bool Deque_##T##_equal(const Deque_##T &deque1, const Deque_##T &deque2) { \
    if (strcmp(deque1.type_name, deque2.type_name)==0 && deque1.arr_length == deque2.arr_length) \
    { \
        for (int i=0; i<deque1.arr_length; i++) \
            if (deque1.less(deque1.arr[(deque1.front_index+i)%deque1.max_length], deque2.arr[(deque2.front_index+i)%deque2.max_length])==true || deque1.less(deque2.arr[(deque2.front_index+i)%deque2.max_length], deque1.arr[(deque1.front_index+i)%deque1.max_length])==true) return false; \
        return true; \
    } \
    else return false; \
} \
bool Deque_##T##_Iterator_equal(const Deque_##T##_Iterator it1, const Deque_##T##_Iterator it2) { \
    if (it1.arr_iterator == it2.arr_iterator && it1.index == it2.index) return true; \
    else return false; \
}

#endif