//
// Created by binbin on 2024/4/1.
//
#include <iostream>
#include <thread>
#include "util.h"
#include "tools/readerwriterqueue.h"

class ThreadPool {
public:
    explicit ThreadPool(uint32_t threadNum = std::thread::hardware_concurrency()) : m_done(false), m_joiner(m_threads) {
        for (int i = 0; i < threadNum; i++) {
            m_threads.emplace_back(&ThreadPool::worker_thread, this);
        }
    }
    ~ThreadPool(){
        m_done = true;
    }
    template<typename FunctionType>
    void Submit(FunctionType f)
    {
        m_queue.enqueue(std::function<void()>(f));
    }
    private:
    void worker_thread()
    {
        while (!m_done)
        {
            std::function<void()> task;
            if (m_queue.try_dequeue(task))
            {
                task();
            } else
            {
                std::this_thread::yield(); //当前线程挂起，避免争抢资源
            }
        }
    }

private:
    std::atomic<bool> m_done;
    moodycamel::ReaderWriterQueue<std::function<void()>> m_queue;
    std::vector<std::thread> m_threads;
    util::Joiner m_joiner;
};
int main() {
    ThreadPool tp(3);
    tp.Submit([](){std::cout<<"hello\n";});
    tp.Submit([](){std::cout<<"hello\n";});
    std::cin.get();
}
