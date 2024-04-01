#include <iostream>
#include <optional>
#include <vector>
class Count {
public:
    Count (){
        count = 1;
    }
    void Increase(){
        count++;
    }
    void Decrease(){
        count--;
    }
    int GetCount() {
        return count;
    }
private:
    int count{0};
};
template<typename T>
class Shared {
public:
    Shared():ptr_(nullptr), c_(nullptr) {}
    explicit Shared(T* ptr) : ptr_(ptr), c_(new Count()) {}
    ~Shared(){
        if (c_ != nullptr) {
            c_->Decrease();
            if (c_->GetCount() == 0) {
                delete c_;
                delete ptr_;
                c_ = nullptr;
                ptr_ = nullptr;
            }
        }
    }

    Shared(const Shared<T>& other) {
        ptr_ = other.ptr_;
        c_ = other.c_;
        c_->Increase();
    }
    Shared<T>& operator=(const Shared<T>& other) {
        if (ptr_ == other.ptr_) {
            return *this;
        }
        ptr_ = other.ptr_;
        c_ = other.c_;
        c_->Increase();
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
        return c_->GetCount();
    }

private:
    T* ptr_;
    Count* c_;
};
class A{
public:
    int m_;
};
int main() {
    Shared<A> p0;
    std::cout << p0.GetCnt()<<std::endl;
    {
        Shared<A> p1(new A());
        std::cout << p1.GetCnt()<<std::endl;
        Shared<A> p2(p1);
        std::cout << p1.GetCnt()<<std::endl;
        p0 = p2;
        std::cout << p0.GetCnt()<<std::endl;
    }
    std::cout << p0.GetCnt()<<std::endl;
    return 0;
}