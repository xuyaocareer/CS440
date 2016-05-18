

#ifndef smartptr_SharedPtr_hpp
#define smartptr_SharedPtr_hpp

#include <cstddef>
#include <pthread.h>
#include <iostream>
#include <atomic>
#include <assert.h>

namespace cs540 {
    
    class Base {
    public:
        Base() : ref_count(0) {}
        virtual ~Base() {}
        virtual int inc() {
            ++ref_count;
            return ref_count;
        }
        virtual int dec() {
            --ref_count;
            return ref_count;
        }
    protected:
        std::atomic_int ref_count;
    };
    
    template <typename U>
    class Shared : public Base {
    public:
        Shared(U* p) : ptr(p) {};
        virtual ~Shared() {
            delete ptr;
        }
    private:
        U* ptr;
    };
    
    
    template <typename T>
    class SharedPtr {
        
        template <typename U>
        friend class SharedPtr;
        
    private:
        T *ptr;
        Base *b_ptr;
        pthread_mutex_t* lock_ptr;
        
    public:
        // constructors
        SharedPtr() : ptr(nullptr), b_ptr(nullptr), lock_ptr(nullptr) {}
        template <typename U>  explicit SharedPtr(U* p) {
            ptr = p;
            b_ptr = new Shared<U>(p);
            lock_ptr = new pthread_mutex_t;
            assert(pthread_mutex_init(lock_ptr, nullptr) == 0);
            if (b_ptr != nullptr)
                b_ptr->inc();
        }
        SharedPtr(SharedPtr& p) {
            ptr = p.ptr;
            b_ptr = p.b_ptr;
            lock_ptr = p.lock_ptr;
            if (b_ptr != nullptr)
                b_ptr->inc();
        }
        template <typename U> SharedPtr(SharedPtr<U>& p) {
            ptr = static_cast<T* >(p.ptr);
            b_ptr = p.b_ptr;
            lock_ptr = p.lock_ptr;
            if (b_ptr != nullptr)
                b_ptr->inc();
        }
        SharedPtr(SharedPtr&& p) {
            ptr = std::move(p.ptr);
            b_ptr = std::move(p.b_ptr);
            lock_ptr = std::move(p.lock_ptr);
            p.ptr = nullptr;
            p.b_ptr = nullptr;
            p.lock_ptr = nullptr;
        }
        template <typename U> SharedPtr(SharedPtr<U>&& p) {
            ptr = std::move(static_cast<T* >(p.ptr));
            b_ptr = std::move(p.b_ptr);
            lock_ptr = std::move(p.lock_ptr);
            p.ptr = nullptr;
            p.b_ptr = nullptr;
            p.lock_ptr = nullptr;
        }
        ~SharedPtr() {
            reset(nullptr);
        }
        
        // member functions
        T* get() const {
            return ptr;
        }
        template <typename U> void reset(U* p) {
            reset(nullptr);
            ptr = static_cast<T* >(p);
            b_ptr = new Shared<U>(p);
            lock_ptr = new pthread_mutex_t;
            assert(pthread_mutex_init(lock_ptr, nullptr) == 0);
            if (b_ptr != nullptr)
                b_ptr->inc();
        }
        void reset(std::nullptr_t) {
            if (b_ptr != nullptr) {
                assert(pthread_mutex_lock(lock_ptr) == 0);
                int shared_num = b_ptr->dec();
                if (shared_num == 0) {
                    delete b_ptr;
                    assert(pthread_mutex_unlock(lock_ptr) == 0);
                    assert(pthread_mutex_destroy(lock_ptr) == 0);
                    delete lock_ptr;
                }
                else {
                    assert(pthread_mutex_unlock(lock_ptr) == 0);
                }
                ptr = nullptr;
                b_ptr = nullptr;
                lock_ptr = nullptr;
            }
        }
        
        // operators
        SharedPtr& operator=(SharedPtr&& p) {
            reset(nullptr);
            ptr = std::move(p.ptr);
            b_ptr = std::move(p.b_ptr);
            lock_ptr = std::move(p.lock_ptr);
            p.ptr = nullptr;
            p.b_ptr = nullptr;
            p.lock_ptr = nullptr;
            return *this;
        }
        template <typename U> SharedPtr& operator=(SharedPtr<U>&& p) {
            reset(nullptr);
            ptr = std::move(static_cast<T* >(p.ptr));
            b_ptr = std::move(p.b_ptr);
            lock_ptr = std::move(p.lock_ptr);
            p.ptr = nullptr;
            p.b_ptr = nullptr;
            p.lock_ptr = nullptr;
            return *this;
        }
        SharedPtr& operator=(const SharedPtr& p) {
            reset(nullptr);
            ptr = p.ptr;
            b_ptr = p.b_ptr;
            if (b_ptr != nullptr)
                b_ptr->inc();
            lock_ptr = p.lock_ptr;
            return *this;
        }
        template <typename U> SharedPtr& operator=(SharedPtr<U>& p) {
            reset(nullptr);
            ptr = static_cast<T* >(p.ptr);
            b_ptr = p.b_ptr;
            if (b_ptr != nullptr)
                b_ptr->inc();
            lock_ptr = p.lock_ptr;
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
    };
    
    // comparison operators
    template <typename T1, typename T2>
    bool operator==(const SharedPtr<T1>& t1, const SharedPtr<T2>& t2) {
        return (t1.get()==t2.get());
    }
    template <typename T1>
    bool operator==(const SharedPtr<T1>& t1, std::nullptr_t) {
        return (t1.get()==nullptr);
    }
    template <typename T1>
    bool operator==(std::nullptr_t, const SharedPtr<T1>& t1) {
        return (t1.get()==nullptr);
    }
    template <typename T1, typename T2>
    bool operator!=(const SharedPtr<T1>& t1, const SharedPtr<T2>& t2) {
        return !(t1==t2);
    }
    template <typename T1>
    bool operator!=(const SharedPtr<T1>& t1, std::nullptr_t) {
        return (t1.get()!=nullptr);
    }
    template <typename T1>
    bool operator!=(std::nullptr_t, const SharedPtr<T1>& t1) {
        return (t1.get()!=nullptr);
    }
    
}

#endif


