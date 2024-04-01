//
// Created by binbin on 2024/4/1.
//

#ifndef LEARNCPP_UTIL_H
#define LEARNCPP_UTIL_H
#include <thread>
#include <vector>
namespace util {
    class Joiner {
    public:
        explicit Joiner(std::vector<std::thread>& threads) : m_threads(threads){}
        ~Joiner() {
            for (auto &&th : m_threads){
                if (th.joinable()) {
                    th.join();
                }
            }
        }
    private:
        std::vector<std::thread>& m_threads;
    };
}


#endif //LEARNCPP_UTIL_H
