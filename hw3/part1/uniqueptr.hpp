

#ifndef smartptr_uniqueptr_hpp
#define smartptr_uniqueptr_hpp

#include <cstddef>
#include <iostream>


namespace cs540 {
    
    class Base {
    public:
        Base() {}
        virtual ~Base() {}
    };
    
    template <typename U>
    class Derived : public Base {
    public:
        Derived(U* p) : ptr(p) {};
        virtual ~Derived() {
            delete ptr;
        }
    private:
        U* ptr;
    };
    
    
    template <typename T>
    class UniquePtr {
        
        template <typename U>
        friend class UniquePtr;
        
    private:
        T* ptr;
        Base *b_ptr;
        
    public:
        // constructors
        UniquePtr() : ptr(nullptr), b_ptr(nullptr) {}
        template <typename U>  explicit UniquePtr(U* p) {
            ptr = p;
            b_ptr = new Derived<U>(p);
        }
        UniquePtr(UniquePtr&& p) {
            ptr = p.ptr;
            b_ptr = std::move(p.b_ptr);
            p.ptr = nullptr;
            p.b_ptr = nullptr;
        }
        template <typename U> UniquePtr(UniquePtr<U>&& p) {
            ptr = static_cast<T* >(p.ptr);
            b_ptr = std::move(p.b_ptr);
            p.ptr = nullptr;
            p.b_ptr = nullptr;
        }
        ~UniquePtr() {
            reset(nullptr);
        }
        UniquePtr(const UniquePtr& ) = delete;
        
        // member functions
        T* get() const {
            return ptr;
        }
        template <typename U> void reset(U* p) {
            if (b_ptr!=nullptr && ptr!=nullptr) {
                delete b_ptr;
                b_ptr = nullptr;
                ptr = nullptr;
            }
            ptr = p;
            b_ptr = new Derived<U>(p);
        }
        void reset(std::nullptr_t) {
            if (b_ptr!=nullptr && ptr!=nullptr) {
                delete b_ptr;
                b_ptr = nullptr;
                ptr = nullptr;
            }
        }
        
        // operators
        UniquePtr& operator=(UniquePtr&& p) {
            reset(nullptr);
            ptr = p.ptr;
            b_ptr = std::move(p.b_ptr);
            p.ptr = nullptr;
            p.b_ptr = nullptr;
            return *this;
        }
        template <typename U> UniquePtr& operator=(UniquePtr<U>&& p) {
            reset(nullptr);
            ptr = static_cast<T* >(p.ptr);
            b_ptr = std::move(p.b_ptr);
            p.ptr = nullptr;
            p.b_ptr = nullptr;
            return *this;
        }
        T& operator*() const {
            return *ptr;
        }
        T* operator->() const {
            return ptr;
        }
        explicit operator bool() const {
            return (ptr!=nullptr);
        }
        UniquePtr& operator=(const UniquePtr& ) = delete;
        template <typename U> UniquePtr& operator=(UniquePtr<U>& ) = delete;
    };
    
    // comparison operators
    template <typename T1, typename T2>
    bool operator==(const UniquePtr<T1>& t1, const UniquePtr<T2>& t2) {
        return (t1.get()==t2.get());
    }
    template <typename T1>
    bool operator==(const UniquePtr<T1>& t1, std::nullptr_t) {
        return (t1.get()==nullptr);
    }
    template <typename T1>
    bool operator==(std::nullptr_t, const UniquePtr<T1>& t1) {
        return (t1.get()==nullptr);
    }
    template <typename T1, typename T2>
    bool operator!=(const UniquePtr<T1>& t1, const UniquePtr<T2>& t2) {
        return !(t1==t2);
    }
    template <typename T1>
    bool operator!=(const UniquePtr<T1>& t1, std::nullptr_t) {
        return (t1.get()!=nullptr);
    }
    template <typename T1>
    bool operator!=(std::nullptr_t, const UniquePtr<T1>& t1) {
        return (t1.get()!=nullptr);
    }
    
}

#endif


