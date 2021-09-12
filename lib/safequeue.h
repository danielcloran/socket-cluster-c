#ifndef SAFE_QUEUE
#define SAFE_QUEUE

#include <condition_variable>
#include <mutex>
#include <queue>

// A threadsafe-queue.
template <class T>
class SafeQueue
{
public:
    SafeQueue() : q(), m(), c() {}

    ~SafeQueue() {}

    // Add an element to the queue.
    void enqueue(T t)
    {
        std::lock_guard<std::mutex> lock(m);
        if (q.size() < 100) {
            q.push(t);
        }
        else {
            std::cout << "Message Queue Full, we have problems." << std::endl;
            q.pop();
            q.push(t);
        }

        std::cout<< "Adding to msg Queue size is now: " << q.size() << std::endl;
        c.notify_one();
    }

    // Get the front element.
    // If the queue is empty, wait till a element is avaiable.
    T dequeue(void)
    {
        std::unique_lock<std::mutex> lock(m);
        if (q.empty()) return "empty";

        // while (q.empty())
        // {
        //     // release lock as long as the wait and reaquire it afterwards.
        //     c.wait(lock);
        // }
        T val = q.front();
        q.pop();
        std::cout<< "Removing from msg Queue size is now: " << q.size() << std::endl;
        return val;
    }

    int wait_until_value(void)
    {
        std::unique_lock<std::mutex> lock(m);
        while (q.empty())
        {
            // release lock as long as the wait and reaquire it afterwards.
            c.wait(lock);
        }
        return true;
    }
private:
    std::queue<T> q;
    mutable std::mutex m;
    std::condition_variable c;
};
#endif