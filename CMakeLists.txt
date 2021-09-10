cmake_minimum_required(VERSION 3.20)
project(playground_cpp)

set(CMAKE_CXX_STANDARD 14)

# 查找系统的boost, 目标版本是1.76.0
# COMPONENTS：用来限定boost的filesystem模块
# REQUIRED：  表明必须找到指定的模块，否则会出错
# 上面的find_package命令如果找到boost::filesystem，
# 会在cmake中设置一些变量，比如Boost_LIBRARIES、Boost_INCLUDE_DIRS，需要在编译目标上使用这些变量。
find_package(Boost 1.76.0 REQUIRED COMPONENTS filesystem)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(playground_cpp main.cpp base/base.cpp base/base.h base/threadpool/thread_pool.cpp base/threadpool/thread_pool.h base/threadpool/main.cpp base/server/server.cpp base/client/client.cpp)