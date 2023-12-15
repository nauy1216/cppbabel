cmake_minimum_required(VERSION 3.26)
project(cppbabel)
set(CMAKE_CXX_STANDARD 17)

# 输出宏展开后的文件
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -E -dD")

# 设置构建类型为 Debug
# 可以设置为"Debug"、"Release"、"RelWithDebInfo" 
# 如果想进行调试必须构建Debug文件
set(CMAKE_BUILD_TYPE Debug)

# =================vars START===============================
#编译的二进制文件
set(BABEL_BINARY ${CMAKE_PROJECT_NAME})
#链接库
set(BABEL_BINARY_LIB ${CMAKE_PROJECT_NAME}_lib)
#编译的单元测试二进制文件
set(BABEL_BINARY_TEST ${CMAKE_PROJECT_NAME}_test)

# rttr_core
set(BABEL_RTTR_CORE rttr_core)
# =================vars START===============================

# =================RTTR START===============================
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
# =================RTTR END===============================

# =================dbg-macro START===============================
add_definitions(-DDBG_MACRO_NO_WARNING)
# header only
include_directories(libs/dbg-macro)
add_subdirectory(libs/dbg-macro)
# =================dbg-macro END===============================

# =================utfcpp START===============================
# header only
include_directories(libs/utfcpp/source)
add_subdirectory(libs/utfcpp)
# =================utfcpp END===============================


# =================cppbabel START===============================
# 这里是为了让packages下的头文件全局可见
include_directories(packages)
add_subdirectory(packages)
# =================cppbabel START===============================



# =================googletest START===============================
add_subdirectory(__test__)
add_subdirectory(libs/googletest)
# =================googletest END===============================
