#include <atomic>
#include "AbstractSynchronizer.h"

template <typename T>
class ActiveSynchronizer: public AbstractSynchronizer<T>{
private:
    std::atomic<bool> busy;
public:
    ActiveSynchronizer(): busy(false){}

    void add(const T &data) override{
        while(true) {
            bool desired = false;
            if (busy.compare_exchange_strong(desired, true)) {
                this->q.push(data);
                busy.store(false);
                return;
            }
        }

    }

    T get() override{
        T data;
        while(true) {
            bool desired = false;
            if (!this->buffer.empty() && busy.compare_exchange_strong(desired, true)) {
                data = this->buffer.front();
                this->buffer.pop();
                busy.store(false);
                return data;
            }
        }

    }

};
