#include <iostream>
#include <optional>
#include <vector>

template<typename T>
class Shared {
public:
    explicit Shared(T* ptr)
    : ptr_(ptr)
    , c_(new int{1})
    , mutex_(new std::mutex)
    {}

    ~Shared(){
        Release();
    }

    Shared(const Shared<T>& other) : mutex_(other.mutex_), ptr_(other.ptr_), c_(other.c_) {
        AddRefCount();
    }
    Shared<T>& operator=(const Shared<T>& other) {
        if (this != &other) {
            Release();
            mutex_ = other.mutex_;
            ptr_ = other.ptr_;
            c_ = other.c_;
            AddRefCount();
        }
        return *this;
    }
    T* get() {
        return ptr_;
    }
    T* operator->() {
        return ptr_;
    }
    T& operator*() {
        return *ptr_;
    }
    int GetCnt() {
        if (c_ == nullptr) return 0;
        return *c_;
    }
private:
    void Release() {
        if (mutex_ == nullptr) return;
        bool del_flag = false;
        {
            std::lock_guard<std::mutex> lock(*mutex_);
            if (c_ != nullptr) {
                --(*c_);
                if (*c_ == 0) {
                    delete c_;
                    delete ptr_;
                    del_flag = true;
                }
            }
        }
        if (del_flag) delete mutex_;
    }

    void AddRefCount()
    {
        mutex_->lock();
        ++(*c_);
        mutex_->unlock();
    }

private:
    T* ptr_;
    int* c_;
    std::mutex* mutex_;
};
class A{
public:
    int m_;
};
int main() {
    Shared<A> p0{new A{5}};
    std::cout << p0.GetCnt()<<std::endl;
    {
        Shared<A> p1(p0);
        std::cout << p1.GetCnt()<<std::endl;
        Shared<A> p2(p1);
        std::cout << p2.GetCnt()<<std::endl;
        p0 = p2;
        std::cout << p0.GetCnt()<<std::endl;
    }
    std::cout << p0.GetCnt()<<std::endl;

    std::shared_ptr<int> p_int = std::make_shared<int>();
    p_int.operator=(std::shared_ptr<int>());
    return 0;
}