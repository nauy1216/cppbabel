# 指定文件夹内所有*.h *.cpp文件
# file(GLOB_RECURSE PACKAGES_SOURCES LIST_DIRECTORIES true *.h *.cpp)
# set(SOURCES ${PACKAGES_SOURCES})

# set(PACKAGES_HEADER_FILES babel-types/utils.h)
# set(PACKAGES_SOURCE_FILES main.cpp 
#                           babel-types/utils.cpp)

# 引入自定义设置
include(source.cmake)

# add_executable(cppbabel ${PACKAGES_SOURCES})
# 生成可执行文件
add_executable(${BABEL_BINARY}  ${PACKAGES_HEADER_FILES} ${PACKAGES_SOURCE_FILES})


# 链接 RTTR 库到你的目标
target_link_libraries(${BABEL_BINARY} ${BABEL_RTTR_CORE})



#设置 BINARY 为项目名IndexProject
# set(BINARY ${CMAKE_PROJECT_NAME})
 
# 1
# add_executable(ExampleProject main.cpp file1.cpp file1.h)
 
# 2
# file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
# set(SOURCES ${SOURCES})
# add_executable(${BINARY}_run ${SOURCES})
# 生成链接库文件
# 为了让单元测试的时候src下的代码能被作为静态链接库使用
add_library(${BABEL_BINARY_LIB} STATIC ${PACKAGES_HEADER_FILES} ${PACKAGES_SOURCE_FILES})
