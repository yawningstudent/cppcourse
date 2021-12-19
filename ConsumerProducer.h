#ifndef UNTITLED_CONSUMERPRODUCER_H
#define UNTITLED_CONSUMERPRODUCER_H

#include "AbstractSynchronizer.h"
#include <memory>
#include <chrono>
#include <thread>
#include <iostream>
#include <future>

template<class C, typename T, size_t interval_ms = 1, size_t iterations = 100>
class ConsumerProducer {
    std::unique_ptr<SynchronizerFactory<T>> factory;
    std::unique_ptr<AbstractSynchronizer<T>> buffer;
public:
    ConsumerProducer(SynchronizerFactory<T> *factory) : factory(factory), buffer(factory->create()) {}

    void produce() {
        for (int i = 0; i < iterations; i++) {
            auto data = std::chrono::high_resolution_clock::now();
            buffer->add(data);
            std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
        }
    }

    void consume() {
        unsigned long long avg = 0;
        for (int i = 0; i < iterations; i++) {
            T start = buffer->get();
            T finish = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
            avg += duration;
        }
        std::cout << "Avg time: " << avg / iterations << " ns" << std::endl;

    }

    void start() {
        auto future = std::async(std::launch::async, &ConsumerProducer::consume, this);
        produce();
        future.wait();
    }
};


#endif //UNTITLED_CONSUMERPRODUCER_H
