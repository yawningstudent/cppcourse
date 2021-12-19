cmake_minimum_required(VERSION 3.21)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp AbstractSynchronizer.h ConsumerProducer.cpp ConsumerProducer.h ConditionSynchronizer.cpp ActiveSynchronizer.cpp)
