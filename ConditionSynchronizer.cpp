#include <mutex>
#include <condition_variable>
#include "AbstractSynchronizer.h"

template<typename T>
class ConditionSynchronizer : public AbstractSynchronizer<T> {
private:
    std::mutex m;
    std::condition_variable cv;
public:
    void add(T data) override {
        std::lock_guard<std::mutex> lg(m);
        this->buffer.push(data);
        cv.notify_all();
    }

    T get() override {
        std::unique_lock<std::mutex> ul(m);
        cv.wait(ul, [this] { return !this->buffer.empty(); });
        T data = this->buffer.front();
        this->buffer.pop();
        ul.unlock();
        return data;
    }
};
