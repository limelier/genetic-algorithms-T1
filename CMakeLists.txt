cmake_minimum_required(VERSION 3.15)
project(t1_project)

set(CMAKE_CXX_STANDARD 17)

add_executable(t1_project main.cpp util/bitset.cpp util/bitset.h util/functions.cpp util/functions.h src/methods.cpp src/methods.h util/result.h config.h util/random.cpp util/random.h)


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(t1_project Threads::Threads)