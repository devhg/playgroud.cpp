cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 14)
# 增加一个flag sanitize=address .
set(CMAKE_CXX_FLAGS "-fsanitize=address")
set(VCPKG_ROOT "/Users/devhg/cpp/vcpkg")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
                            CACHE STRING Vcpkg toolchain file")
if (DEFINED ENV{VCPKG_DEFAULT_TRIPLET} AND NOT DEFINED VCPKG_TARGET_TRIPLET)
    set(VCPKG_TARGET_TRIPLET "$ENV{VCPKG_DEFAULT_TRIPLET}" CACHE STRING "")
endif ()

project(playground_cpp)
add_executable(playground_cpp main.cpp)

# 第三方库
set(VCPKG_3RD_PARTY_ROOT "${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}")
set(VCPKG_3RD_PARTY_INCLUDE "${VCPKG_3RD_PARTY_ROOT}/include")
set(VCPKG_3RD_PARTY_LIB "${VCPKG_3RD_PARTY_ROOT}/lib")

# 指定头文件搜索路径 为所有子工程增加附加引用头文件目录 ${VCPKG_3RD_PARTY_INCLUDE}
include_directories(${VCPKG_3RD_PARTY_INCLUDE})
# 指定引用的外部库的搜索路径
link_directories(${VCPKG_3RD_PARTY_LIB})

find_package(fmt CONFIG REQUIRED)
message("fmt found " + ${fmt_VERSION})
target_link_libraries(playground_cpp PRIVATE fmt::fmt)

find_package(jsoncpp CONFIG REQUIRED)
message("jsoncpp found " + ${jsoncpp_VERSION})
target_link_libraries(playground_cpp PRIVATE jsoncpp_object jsoncpp_static JsonCpp::JsonCpp)


find_package(Boost REQUIRED)
message("Boost found " + ${Boost_VERSION})
# 什么区别？？？
#target_link_libraries(playground_cpp PRIVATE Boost::boost ${Boost_LIBRARIES})
#target_link_libraries(playground_cpp PRIVATE ${Boost_LIBRARIES})
target_link_libraries(playground_cpp PRIVATE Boost::boost)
