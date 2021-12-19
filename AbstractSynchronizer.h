#ifndef UNTITLED_ABSTRACTSYNCHRONIZER_H
#define UNTITLED_ABSTRACTSYNCHRONIZER_H

#include <queue>
#include <map>

template<typename T>
class AbstractSynchronizer {
protected:
    std::queue<T> buffer;
public:
    virtual void add(T data) = 0;

    virtual T get() = 0;
};

template<typename T>
class AbstractSynchronizerCreator {
public:
    virtual AbstractSynchronizer<T> *create() const = 0;
};

template<class C, typename T>
class SynchronizerCreator : public AbstractSynchronizerCreator<T> {
public:
    virtual AbstractSynchronizer<T> *create() const { return new C(); }
};

template<typename T>
class SynchronizerFactory {
protected:
    typedef std::map<std::string, AbstractSynchronizerCreator<T> *> FactoryMap;
    FactoryMap _factory;
public:
    template<class C>
    void addType(const std::string &id) {
        typename FactoryMap::iterator it = _factory.find(id);
        if (it == _factory.end())
            _factory[id] = new SynchronizerCreator<C, T>();
    }

    AbstractSynchronizer<T> *create(const std::string &id) {
        typename FactoryMap::iterator it = _factory.find(id);
        if (it != _factory.end())
            return it->second->create();
        return 0;
    }
};

#endif //UNTITLED_ABSTRACTSYNCHRONIZER_H
