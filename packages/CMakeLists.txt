# cmake_minimum_required(VERSION 3.26)
# project(cppbabel)

# set(CMAKE_CXX_STANDARD 17)

# # 设置 RTTR 的编译选项
# set(BUILD_RTTR_DYNAMIC ON)
# set(BUILD_UNIT_TESTS OFF)
# set(BUILD_STATIC OFF)
# set(BUILD_WITH_STATIC_RUNTIME_LIBS OFF)
# set(BUILD_WITH_RTTI ON)
# set(BUILD_BENCHMARKS OFF)
# set(BUILD_EXAMPLES OFF)
# set(BUILD_DOCUMENTATION OFF)
# set(BUILD_INSTALLER OFF)
# set(BUILD_PACKAGE OFF)
# set(USE_PCH OFF)
# set(CUSTOM_DOXYGEN_STYLE OFF)
# set(BUILD_WEBSITE_DOCU OFF)

# # 添加 RTTR 子目录
# add_subdirectory(../libs/rttr)

# 添加你的项目源代码目录
# add_subdirectory(packages)

# 这里是为了让packages下的头文件全局可见
# include_directories(packages)

# file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
add_executable(cppbabel main.cpp)


# 链接 RTTR 库到你的目标
target_link_libraries(cppbabel ${BABEL_RTTR_CORE})



#设置 BINARY 为项目名IndexProject
# set(BINARY ${CMAKE_PROJECT_NAME})
 
# 1
# add_executable(ExampleProject main.cpp file1.cpp file1.h)
 
# 2
# file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
# set(SOURCES ${SOURCES})
# add_executable(${BINARY}_run ${SOURCES})
# 为了让单元测试的时候src下的代码能被作为静态链接库使用
add_library(${BABEL_BINARY_LIB} STATIC main.cpp)
