
#ifndef Array_Array_hpp
#define Array_Array_hpp

#include <assert.h>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <stdexcept>

namespace cs540 {
    
    class OutOfRange : public std::runtime_error {
    public:
        OutOfRange(const std::string &message) : runtime_error("Error: " + message) {
        }
    };
    
    class WrongTemplate : public std::runtime_error {
    public:
        WrongTemplate(const std::string &message) : runtime_error("Error: " + message) {
        }
    };
    
    
    
    
    
    
    // Array class declaration
    template <typename T, size_t D, size_t... Dims>
    class Array {
    public:
        // type members
        typedef T ValueType;
        class FirstDimensionMajorIterator;
        class LastDimensionMajorIterator;
        class ConstFirstDimensionMajorIterator;
        class ConstLastDimensionMajorIterator;
        friend class Array<T, Dims...>;
        
        // member variables
        Array<T, Dims...>* arr_ptr;
        size_t size;
        size_t dim_size;
        
    public:
        // Public Member Functions
        Array() : size(D), dim_size(sizeof...(Dims)) {
            if (D <= 0)
                throw OutOfRange("non-positive dimension");
            arr_ptr = new Array<T, Dims...>[D];
        }
        
        Array(const Array &arr_in) : size(D), dim_size(sizeof...(Dims)) {
            arr_ptr = new Array<T, Dims...>[D];
            for (size_t i=0; i<D; i++) {
                arr_ptr[i] = arr_in.arr_ptr[i];
            }
        }
        
        template <typename U>
        Array(const Array<U, D, Dims...> &arr_in) : size(D), dim_size(sizeof...(Dims)){
            arr_ptr = new Array<T, Dims...>[D];
            for (size_t i=0; i<D; i++) {
                arr_ptr[i] = arr_in.arr_ptr[i];
            }
        }
        
        Array &operator=(const Array &arr_in) {
            if (arr_ptr == arr_in.arr_ptr) { // self-assignment, no-op
                return *this;
            }
            else {
                if (size==arr_in.size && dim_size==arr_in.dim_size) {
                    for (size_t i=0; i<size; i++) {
                        arr_ptr[i] = arr_in.arr_ptr[i];
                    }
                }
                else {
                    throw WrongTemplate("dimensions do not match");
                }
                return *this;
            }
        }
        
        template <typename U>
        Array &operator=(const Array<U, D, Dims...> &arr_in) {
            if (size==arr_in.size && dim_size==arr_in.dim_size) {
                for (size_t i=0; i<size; i++) {
                    arr_ptr[i] = arr_in.arr_ptr[i];
                }
            }
            else {
                throw WrongTemplate("dimensions do not match");
            }
            return *this;
        }
        
        Array<T, Dims...>& operator[] (const size_t d) {
            if (size <= d) {
                throw OutOfRange("out of range");
            }
            else {
                return arr_ptr[d];
            }
        }
        
        const Array<T, Dims...>& operator[] (const size_t d) const {
            if (size <= d) {
                throw OutOfRange("out of range");
            }
            else {
                return arr_ptr[d];
            }
        }
        
        ~Array() {
            delete[] arr_ptr;
        }
        
        // iterators
        FirstDimensionMajorIterator fmbegin() {
            FirstDimensionMajorIterator f;
            f.ptr = this;
            f.index = 0;
            f.element = arr_ptr[0].fmbegin();
            return f;
        }
        
        FirstDimensionMajorIterator fmend() {
            FirstDimensionMajorIterator f;
            f.ptr = this;
            f.index = this->size;
            f.element = arr_ptr[size-1].fmend();
            return f;
        }
        
        friend bool operator==(const FirstDimensionMajorIterator &f_iter1, const FirstDimensionMajorIterator &f_iter2) {
            if (f_iter1.ptr==f_iter2.ptr && f_iter1.size==f_iter2.size && f_iter1.index==f_iter2.index && f_iter1.element==f_iter2.element)
                return true;
            else
                return false;
        }
        
        friend bool operator!=(const FirstDimensionMajorIterator &f_iter1, const FirstDimensionMajorIterator &f_iter2) {
            if (f_iter1 == f_iter2)
                return false;
            else
                return true;
        }
        
        LastDimensionMajorIterator lmbegin() {
            LastDimensionMajorIterator l;
            l.ptr = this;
            l.index = 0;
            l.element = arr_ptr[0].lmbegin();
            return l;
        }
        
        LastDimensionMajorIterator lmend() {
            LastDimensionMajorIterator l;
            l.ptr = this;
            l.index = 0;
            l.element = arr_ptr[0].lmend();
            return l;
        }
        
        friend bool operator==(const LastDimensionMajorIterator &l_iter1, const LastDimensionMajorIterator &l_iter2) {
            if (l_iter1.ptr==l_iter2.ptr && l_iter1.size==l_iter2.size && l_iter1.index==l_iter2.index && l_iter1.element==l_iter2.element)
                return true;
            else
                return false;
        }
        
        friend bool operator!=(const LastDimensionMajorIterator &l_iter1, const LastDimensionMajorIterator &l_iter2) {
            if (l_iter1 == l_iter2)
                return false;
            else
                return true;
        }
        
        // const iterators
        ConstFirstDimensionMajorIterator fmbegin() const {
            ConstFirstDimensionMajorIterator f;
            f.ptr = this;
            f.index = 0;
            f.element = arr_ptr[0].fmbegin();
            return f;
        }
        
        ConstFirstDimensionMajorIterator fmend() const {
            ConstFirstDimensionMajorIterator f;
            f.ptr = this;
            f.index = this->size;
            f.element = arr_ptr[size-1].fmend();
            return f;
        }
        
        friend bool operator==(const ConstFirstDimensionMajorIterator &f_iter1, const ConstFirstDimensionMajorIterator &f_iter2) {
            if (f_iter1.ptr==f_iter2.ptr && f_iter1.size==f_iter2.size && f_iter1.index==f_iter2.index && f_iter1.element==f_iter2.element)
                return true;
            else
                return false;
        }
        
        friend bool operator!=(const ConstFirstDimensionMajorIterator &f_iter1, const ConstFirstDimensionMajorIterator &f_iter2) {
            if (f_iter1 == f_iter2)
                return false;
            else
                return true;
        }
        
        ConstLastDimensionMajorIterator lmbegin() const{
            ConstLastDimensionMajorIterator l;
            l.ptr = this;
            l.index = 0;
            l.element = arr_ptr[0].lmbegin();
            return l;
        }
        
        ConstLastDimensionMajorIterator lmend() const{
            ConstLastDimensionMajorIterator l;
            l.ptr = this;
            l.index = 0;
            l.element = arr_ptr[0].lmend();
            return l;
        }
        
        friend bool operator==(const ConstLastDimensionMajorIterator &l_iter1, const ConstLastDimensionMajorIterator &l_iter2) {
            if (l_iter1.ptr==l_iter2.ptr && l_iter1.size==l_iter2.size && l_iter1.index==l_iter2.index && l_iter1.element==l_iter2.element)
                return true;
            else
                return false;
        }
        
        friend bool operator!=(const ConstLastDimensionMajorIterator &l_iter1, const ConstLastDimensionMajorIterator &l_iter2) {
            if (l_iter1 == l_iter2)
                return false;
            else
                return true;
        }
    };
    
    
    
    template <typename T, size_t D>
    class Array <T, D> {
    public:
        // type members
        typedef T ValueType;
        class FirstDimensionMajorIterator;
        class LastDimensionMajorIterator;
        class ConstFirstDimensionMajorIterator;
        class ConstLastDimensionMajorIterator;
        
        // member variables
        T* arr_ptr;
        size_t size;
        size_t dim_size;
        
    public:
        // Public Member Functions
        Array() : size(D), dim_size(0) {
            if (D <= 0)
                throw OutOfRange("non-positive dimension");
            arr_ptr = new T[D];
        }
        
        Array(const Array &arr_in) : size(D), dim_size(0) {
            arr_ptr = new T[D];
            for (size_t i=0; i<D; i++) {
                arr_ptr[i] = arr_in.arr_ptr[i];
            }
        }
        
        template <typename U>
        Array(const Array<U, D> &arr_in) : size(D), dim_size(0){
            arr_ptr = new T[D];
            for (size_t i=0; i<D; i++) {
                arr_ptr[i] = arr_in.arr_ptr[i];
            }
        }
        
        Array &operator=(const Array &arr_in) {
            if (arr_ptr == arr_in.arr_ptr) { // self-assignment, no-op
                return *this;
            }
            else {
                if (size==arr_in.size && dim_size==arr_in.dim_size) {
                    for (size_t i=0; i<size; i++) {
                        arr_ptr[i] = arr_in.arr_ptr[i];
                    }
                }
                else {
                    throw WrongTemplate("dimensions do not match");
                }
                return *this;
            }
        }
        
        template <typename U>
        Array &operator=(const Array<U, D> &arr_in) {
            if (size==arr_in.size && dim_size==arr_in.dim_size) {
                for (size_t i=0; i<size; i++) {
                    arr_ptr[i] = arr_in.arr_ptr[i];
                }
            }
            else {
                throw WrongTemplate("dimensions do not match");
            }
            return *this;
        }
        
        T& operator[] (const size_t d) {
            if (size <= d) {
                throw OutOfRange("out of range");
            }
            else {
                return arr_ptr[d];
            }
        }
        
        const T& operator[] (const size_t d) const {
            if (size <= d) {
                throw OutOfRange("out of range");
            }
            else {
                return arr_ptr[d];
            }
        }
        
        ~Array() {
            delete[] arr_ptr;
        }
        
        // iterators
        FirstDimensionMajorIterator fmbegin() {
            FirstDimensionMajorIterator f;
            f.ptr = this;
            f.index = 0;
            f.element = &(arr_ptr[0]);
            return f;
        }
        
        FirstDimensionMajorIterator fmend() {
            FirstDimensionMajorIterator f;
            f.ptr = this;
            f.index = this->size;
            f.element = &(arr_ptr[0]);
            return f;
        }
        
        friend bool operator==(const FirstDimensionMajorIterator &f_iter1, const FirstDimensionMajorIterator &f_iter2) {
            if (f_iter1.ptr==f_iter2.ptr && f_iter1.size==f_iter2.size && f_iter1.index==f_iter2.index && f_iter1.element==f_iter2.element)
                return true;
            else
                return false;
        }
        
        friend bool operator!=(const FirstDimensionMajorIterator &f_iter1, const FirstDimensionMajorIterator &f_iter2) {
            if (f_iter1 == f_iter2)
                return false;
            else
                return true;
        }
        
        LastDimensionMajorIterator lmbegin() {
            LastDimensionMajorIterator l;
            l.ptr = this;
            l.index = 0;
            l.element = &(arr_ptr[0]);
            return l;
        }
        
        LastDimensionMajorIterator lmend() {
            LastDimensionMajorIterator l;
            l.ptr = this;
            l.index = this->size;
            l.element = &(arr_ptr[0]);
            return l;
        }
        
        friend bool operator==(const LastDimensionMajorIterator &l_iter1, const LastDimensionMajorIterator &l_iter2) {
            if (l_iter1.ptr==l_iter2.ptr && l_iter1.size==l_iter2.size && l_iter1.index==l_iter2.index && l_iter1.element==l_iter2.element)
                return true;
            else
                return false;
        }
        
        friend bool operator!=(const LastDimensionMajorIterator &l_iter1, const LastDimensionMajorIterator &l_iter2) {
            if (l_iter1 == l_iter2)
                return false;
            else
                return true;
        }
        
        // const iterators
        ConstFirstDimensionMajorIterator fmbegin() const {
            ConstFirstDimensionMajorIterator f;
            f.ptr = this;
            f.index = 0;
            f.element = &(arr_ptr[0]);
            return f;
        }
        
        ConstFirstDimensionMajorIterator fmend() const {
            ConstFirstDimensionMajorIterator f;
            f.ptr = this;
            f.index = this->size;
            f.element = &(arr_ptr[0]);
            return f;
        }
        
        friend bool operator==(const ConstFirstDimensionMajorIterator &f_iter1, const ConstFirstDimensionMajorIterator &f_iter2) {
            if (f_iter1.ptr==f_iter2.ptr && f_iter1.size==f_iter2.size && f_iter1.index==f_iter2.index && f_iter1.element==f_iter2.element)
                return true;
            else
                return false;
        }
        
        friend bool operator!=(const ConstFirstDimensionMajorIterator &f_iter1, const ConstFirstDimensionMajorIterator &f_iter2) {
            if (f_iter1 == f_iter2)
                return false;
            else
                return true;
        }
        
        ConstLastDimensionMajorIterator lmbegin() const {
            LastDimensionMajorIterator l;
            l.ptr = this;
            l.index = 0;
            l.element = &(arr_ptr[0]);
            return l;
        }
        
        ConstLastDimensionMajorIterator lmend() const {
            LastDimensionMajorIterator l;
            l.ptr = this;
            l.index = this->size;
            l.element = &(arr_ptr[0]);
            return l;
        }
        
        friend bool operator==(const ConstLastDimensionMajorIterator &l_iter1, const ConstLastDimensionMajorIterator &l_iter2) {
            if (l_iter1.ptr==l_iter2.ptr && l_iter1.size==l_iter2.size && l_iter1.index==l_iter2.index && l_iter1.element==l_iter2.element)
                return true;
            else
                return false;
        }
        
        friend bool operator!=(const ConstLastDimensionMajorIterator &l_iter1, const ConstLastDimensionMajorIterator &l_iter2) {
            if (l_iter1 == l_iter2)
                return false;
            else
                return true;
        }
    };
    
    
    
    
    
    // iterator class declaration
    // FristDimensionMajorIterator class declaration
	template <typename T, size_t D, size_t... Dims>
	class Array<T, D, Dims...>::FirstDimensionMajorIterator {
    public:
        Array<T, D, Dims...>* ptr;
        size_t size;
        size_t index;
        typename Array<T, Dims...>::FirstDimensionMajorIterator element;
        
    public:
        FirstDimensionMajorIterator() : size(D), index(0) {
        }
        
        FirstDimensionMajorIterator(const FirstDimensionMajorIterator &f_iter) : ptr(f_iter.ptr), size(f_iter.size), index(f_iter.index), element(f_iter.element) {
        }
        
        FirstDimensionMajorIterator& operator=(const FirstDimensionMajorIterator &f_iter) {
            ptr = f_iter.ptr;
            size = f_iter.size;
            index = f_iter.index;
            element = f_iter.element;
            return *this;
        }
        
        FirstDimensionMajorIterator &operator++() {
            ++element;
            if (element.index == element.size) {
                index++;
                if (index < size)
                    element = (ptr->arr_ptr[index]).fmbegin(); // reset next_index = 0
            }
            return *this;
        }
        
        FirstDimensionMajorIterator operator++(int) {
            FirstDimensionMajorIterator f_iter = *this;
            ++(*this);
            return f_iter;
        }
        
        T &operator*() const {
            return *element;
        }
	};
    
    
    
	template <typename T, size_t D>
	class Array<T, D>::FirstDimensionMajorIterator{
    public:
        Array<T, D>* ptr;
        size_t size;
        size_t index;
        T* element;
        
    public:
        FirstDimensionMajorIterator() : size(D), index(0) {
        }
        
        FirstDimensionMajorIterator(const FirstDimensionMajorIterator &f_iter) : ptr(f_iter.ptr), size(f_iter.size), index(f_iter.index), element(f_iter.element) {
        }
        
        FirstDimensionMajorIterator& operator=(const FirstDimensionMajorIterator &f_iter) {
            ptr = f_iter.ptr;
            size = f_iter.size;
            index = f_iter.index;
            element = f_iter.element;
            return *this;
        }
        
        FirstDimensionMajorIterator &operator++() {
            index++;
            if (index == size) // reach the end, do the next iteration
                element = &(ptr->arr_ptr[0]);
            else
                element = &(ptr->arr_ptr[index]);
            return *this;
        }
        
        FirstDimensionMajorIterator operator++(int) {
            FirstDimensionMajorIterator f_iter = *this;
            ++(*this);
            return f_iter;
        }
        
        T &operator*() const {
            return *element;
        }
	};
    
    
    
    // LastDimensionMajorIterator class declaration
	template <typename T, size_t D, size_t... Dims>
	class Array<T, D, Dims...>::LastDimensionMajorIterator {
    public:
        Array<T, D, Dims...>* ptr;
        size_t size;
        size_t index;
        typename Array<T, Dims...>::LastDimensionMajorIterator element;
        
    public:
        LastDimensionMajorIterator() : size(D), index(0) {
        }
        
        LastDimensionMajorIterator(const LastDimensionMajorIterator &l_iter) : ptr(l_iter.ptr), size(l_iter.size), index(l_iter.index), element(l_iter.element) {
        }
        
        LastDimensionMajorIterator& operator=(const LastDimensionMajorIterator &l_iter) {
            ptr = l_iter.ptr;
            size = l_iter.size;
            index = l_iter.index;
            element = l_iter.element;
            return *this;
        }
        
        LastDimensionMajorIterator &operator++() {
            index++;
            if (index == size) { // reach the end, do the next iteration
                ++element;
                index = 0;
            }
            set_ptr();
            return *this;
        }
        
        LastDimensionMajorIterator operator++(int) {
            LastDimensionMajorIterator l_iter = *this;
            ++(*this);
            return l_iter;
        }
        
        void set_ptr() {
            element.ptr = &(ptr->arr_ptr[index]);
            element.set_ptr();
        }
        
        T &operator*() const {
            return *element;
        }
	};
    
    
    
	template <typename T, size_t D>
	class Array<T, D>::LastDimensionMajorIterator{
    public:
        Array<T, D>* ptr;
        size_t size;
        size_t index;
        T* element;
        
    public:
        LastDimensionMajorIterator() : size(D), index(0) {
        }
        
        LastDimensionMajorIterator(const LastDimensionMajorIterator &l_iter) : ptr(l_iter.ptr), size(l_iter.size), index(l_iter.index), element(l_iter.element) {
        }
        
        LastDimensionMajorIterator& operator=(const LastDimensionMajorIterator &l_iter) {
            ptr = l_iter.ptr;
            size = l_iter.size;
            index = l_iter.index;
            element = l_iter.element;
            return *this;
        }
        
        LastDimensionMajorIterator &operator++() {
            index++;
            set_ptr();
            return *this;
        }
        
        LastDimensionMajorIterator operator++(int) {
            LastDimensionMajorIterator l_iter = *this;
            ++(*this);
            return l_iter;
        }
        
        void set_ptr() {
            if (index < size)
                element = &(ptr->arr_ptr[index]);
            else // reach the end, do the next iteration
                element = &(ptr->arr_ptr[0]);
        }
        
        T &operator*() const {
            return *element;
        }
	};
    
    
    
    // const iterator class declaration
    // Const_FristDimensionMajorIterator class declaration
	template <typename T, size_t D, size_t... Dims>
	class Array<T, D, Dims...>::ConstFirstDimensionMajorIterator {
    public:
        const Array<T, D, Dims...>* ptr;
        size_t size;
        size_t index;
        typename Array<T, Dims...>::FirstDimensionMajorIterator element;
        
    public:
        ConstFirstDimensionMajorIterator() : size(D), index(0) {
        }
        
        ConstFirstDimensionMajorIterator(const ConstFirstDimensionMajorIterator &f_iter) : ptr(f_iter.ptr), size(f_iter.size), index(f_iter.index), element(f_iter.element) {
        }
        
        ConstFirstDimensionMajorIterator& operator=(const ConstFirstDimensionMajorIterator &f_iter) {
            ptr = f_iter.ptr;
            size = f_iter.size;
            index = f_iter.index;
            element = f_iter.element;
            return *this;
        }
        
        ConstFirstDimensionMajorIterator &operator++() {
            ++element;
            if (element.index == element.size) {
                index++;
                if (index < size)
                    element = (ptr->arr_ptr[index]).fmbegin(); // reset next_index = 0
            }
            return *this;
        }
        
        ConstFirstDimensionMajorIterator operator++(int) {
            ConstFirstDimensionMajorIterator f_iter = *this;
            ++(*this);
            return f_iter;
        }
        
        const T &operator*() const {
            return *element;
        }
	};
    
    
    
	template <typename T, size_t D>
	class Array<T, D>::ConstFirstDimensionMajorIterator{
    public:
        const Array<T, D>* ptr;
        size_t size;
        size_t index;
        T* element;
        
    public:
        ConstFirstDimensionMajorIterator() : size(D), index(0) {
        }
        
        ConstFirstDimensionMajorIterator(const ConstFirstDimensionMajorIterator &f_iter) : ptr(f_iter.ptr), size(f_iter.size), index(f_iter.index), element(f_iter.element) {
        }
        
        ConstFirstDimensionMajorIterator& operator=(const ConstFirstDimensionMajorIterator &f_iter) {
            ptr = f_iter.ptr;
            size = f_iter.size;
            index = f_iter.index;
            element = f_iter.element;
            return *this;
        }
        
        ConstFirstDimensionMajorIterator &operator++() {
            index++;
            if (index == size) // reach the end, do the next iteration
                element = &(ptr->arr_ptr[0]);
            else
                element = &(ptr->arr_ptr[index]);
            return *this;
        }
        
        ConstFirstDimensionMajorIterator operator++(int) {
            ConstFirstDimensionMajorIterator f_iter = *this;
            ++(*this);
            return f_iter;
        }
        
        const T &operator*() const {
            return *element;
        }
	};
    
    
    
    // ConstLastDimensionMajorIterator class declaration
	template <typename T, size_t D, size_t... Dims>
	class Array<T, D, Dims...>::ConstLastDimensionMajorIterator {
    public:
        const Array<T, D, Dims...>* ptr;
        size_t size;
        size_t index;
        typename Array<T, Dims...>::ConstLastDimensionMajorIterator element;
        
    public:
        ConstLastDimensionMajorIterator() : size(D), index(0) {
        }
        
        ConstLastDimensionMajorIterator(const ConstLastDimensionMajorIterator &l_iter) : ptr(l_iter.ptr), size(l_iter.size), index(l_iter.index), element(l_iter.element) {
        }
        
        ConstLastDimensionMajorIterator& operator=(const ConstLastDimensionMajorIterator &l_iter) {
            ptr = l_iter.ptr;
            size = l_iter.size;
            index = l_iter.index;
            element = l_iter.element;
            return *this;
        }
        
        ConstLastDimensionMajorIterator &operator++() {
            index++;
            if (index == size) { // reach the end, do the next iteration
                ++element;
                index = 0;
            }
            set_ptr();
            return *this;
        }
        
        ConstLastDimensionMajorIterator operator++(int) {
            ConstLastDimensionMajorIterator l_iter = *this;
            ++(*this);
            return l_iter;
        }
        
        void set_ptr() {
            element.ptr = &(ptr->arr_ptr[index]);
            element.set_ptr();
        }
        
        const T &operator*() const {
            return *element;
        }
	};
    
    
    
	template <typename T, size_t D>
	class Array<T, D>::ConstLastDimensionMajorIterator{
    public:
        const Array<T, D>* ptr;
        size_t size;
        size_t index;
        const T* element;
        
    public:
        ConstLastDimensionMajorIterator() : size(D), index(0) {
        }
        
        ConstLastDimensionMajorIterator(const ConstLastDimensionMajorIterator &l_iter) : ptr(l_iter.ptr), size(l_iter.size), index(l_iter.index), element(l_iter.element) {
        }
        
        ConstLastDimensionMajorIterator& operator=(const ConstLastDimensionMajorIterator &l_iter) {
            ptr = l_iter.ptr;
            size = l_iter.size;
            index = l_iter.index;
            element = l_iter.element;
            return *this;
        }
        
        ConstLastDimensionMajorIterator &operator++() {
            index++;
            set_ptr();
            return *this;
        }
        
        ConstLastDimensionMajorIterator operator++(int) {
            ConstLastDimensionMajorIterator l_iter = *this;
            ++(*this);
            return l_iter;
        }
        
        void set_ptr() {
            if (index < size)
                element = &(ptr->arr_ptr[index]);
            else // reach the end, do the next iteration
                element = &(ptr->arr_ptr[0]);
        }
        
        const T &operator*() const {
            return *element;
        }
	};
    
}


#endif
