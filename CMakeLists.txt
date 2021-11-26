cmake_minimum_required(VERSION 3.20)
project(playground_cpp)

set(CMAKE_CXX_STANDARD 14)
# 增加一个flag sanitize=address .
set(CMAKE_CXX_FLAGS "-fsanitize=address")

# 查找系统的boost, 目标版本是1.76.0
# COMPONENTS：用来限定boost的filesystem模块
# REQUIRED：  表明必须找到指定的模块，否则会出错
# 上面的find_package命令如果找到boost::filesystem，
# 会在cmake中设置一些变量，比如Boost_LIBRARIES、Boost_INCLUDE_DIRS，需要在编译目标上使用这些变量。

#find_package(Boost 1.76.0 REQUIRED COMPONENTS filesystem)
#include_directories(${Boost_INCLUDE_DIRS})
#message("cmake_module_path: " ${CMAKE_MODULE_PATH})
#message("cmake_prefix_path: " ${CMAKE_PREFIX_PATH})
#message("a" ${Boost_INCLUDE_DIRS})

add_executable(playground_cpp main.cpp)

find_package(fmt)
if (fmt_FOUND)
    find_package(fmt CONFIG REQUIRED)
    message("fmt found" + ${fmt_VERSION})
    message("fmt found" + ${fmt_INCLUDE_DIRS})
    message("fmt found" + ${fmt_LIBRARIES})
    message("fmt found" + ${fmt_LIB_VERSION})
    target_link_libraries(playground_cpp PRIVATE fmt::fmt)
endif ()

#add_executable(playground_cpp main.cpp base/base.cpp base/base.h base/threadpool/thread_pool.cpp base/threadpool/thread_pool.h base/threadpool/main.cpp base/server/server.cpp base/client/client.cpp)
