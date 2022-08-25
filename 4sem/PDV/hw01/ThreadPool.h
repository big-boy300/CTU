#ifndef PRODUCENTCONSUMER_THREADPOOL_H
#define PRODUCENTCONSUMER_THREADPOOL_H
 
#include <list>
#include <thread>
#include <vector>
#include <iostream>
#include <condition_variable>
#include <mutex>
 
template<typename job_t, typename worker_t>
class ThreadPool {
private:
    // Fronta uloh
    std::list<job_t> queue;
 
    // Vlakna konzumentu zpracovavajicich ulohy
    std::vector<std::thread> threads;
 
    // Funkce, kterou maji konzumenti vykonavat
    const worker_t & worker;
 
    std::mutex mutex;
    std::condition_variable condVar;
 
public:
    ThreadPool(const unsigned int num_threads, const worker_t & worker);
    void process(const job_t job);
    void join();
 
};
 
 
template<typename job_t, typename worker_t>
ThreadPool<job_t, worker_t>::ThreadPool(const unsigned int num_threads, const worker_t &worker) : worker(worker) {
 
    for(int i = 0; i < num_threads; ++i) {
        threads.push_back(std::thread([&]() {
            job_t task;
            do {
                std::unique_lock<std::mutex> lock(mutex);
                //if the queue is not empty, work with data, else continue sleeping
                condVar.wait(lock, [this](){return !queue.empty();});
                task = queue.front();
                queue.pop_front();
                lock.unlock();
 
                if (task != 0) worker(task);
 
            } while (task != 0);
        }));
    }
}
 
template<typename job_t, typename worker_t>
void ThreadPool<job_t, worker_t>::process(const job_t job) {
    std::unique_lock<std::mutex> lock(mutex);
    queue.push_back(job);
    lock.unlock();
    condVar.notify_all();
}
 
// Tato metoda nam umozni volajici funkci v main.cpp pockat na vsechna spustena vlakna konzumentu
template<typename job_t, typename worker_t>
void ThreadPool<job_t, worker_t>::join() {
    for(unsigned int i = 0 ; i < threads.size() ; i++) threads[i].join();
}
 
#endif //PRODUCENTCONSUMER_THREADPOOL_H
