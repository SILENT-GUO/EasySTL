cmake_minimum_required(VERSION 3.14)
project(CLRS-Notes LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 创建一个 header-only 的“接口库”
add_library(data_structures INTERFACE)

# 指定头文件目录
target_include_directories(data_structures
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/data-structures>
        $<INSTALL_INTERFACE:include>  # 如果将来要安装，可选
)

# 主程序依赖这个库
add_executable(my_algo_app main.cpp)
target_link_libraries(my_algo_app PRIVATE data_structures)