//
// Created by binbin on 24-4-16.
//
#include <iostream>
#include <vector>
#include <thread>
using namespace std::chrono_literals;
std::mutex mutex;
std::condition_variable cv;
std::vector<int> vec;

void Consumer() {
    std::unique_lock<std::mutex> lock(mutex);
//    while (vec.empty()) { // 加入此判断条件
//        cv.wait(lock);
//    }
    cv.wait(lock, [&](){ return !vec.empty(); }); // 这里可以直接使用C++的封装
    std::cout << "consumer " << vec.size() << "\n";
}

void Produce() {
    std::unique_lock<std::mutex> lock(mutex);
    vec.push_back(1);
    cv.notify_all();
    std::cout << "produce \n";
}

int main() {
    std::thread t(Consumer);
    t.detach();
    Produce();
    std::this_thread::sleep_for(1s);
    return 0;
}