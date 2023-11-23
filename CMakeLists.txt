cmake_minimum_required(VERSION 3.26)
project(cppbabel)

set(CMAKE_CXX_STANDARD 17)

# 设置 RTTR 的编译选项
set(BUILD_RTTR_DYNAMIC ON)
set(BUILD_UNIT_TESTS OFF)
set(BUILD_STATIC OFF)
set(BUILD_WITH_STATIC_RUNTIME_LIBS OFF)
set(BUILD_WITH_RTTI ON)
set(BUILD_BENCHMARKS OFF)
set(BUILD_EXAMPLES OFF)
set(BUILD_DOCUMENTATION OFF)
set(BUILD_INSTALLER OFF)
set(BUILD_PACKAGE OFF)
set(USE_PCH OFF)
set(CUSTOM_DOXYGEN_STYLE OFF)
set(BUILD_WEBSITE_DOCU OFF)

# 添加 RTTR 子目录
add_subdirectory(libs/rttr)

# 添加你的项目源代码目录
# add_subdirectory(packages)

add_executable(cppbabel main.cpp)

# 链接 RTTR 库到你的目标
target_link_libraries(cppbabel rttr_core)
