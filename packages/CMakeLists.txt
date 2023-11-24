# 引入自定义设置
include(source.cmake)

# =================cppbabel START===============================
# 生成可执行文件
add_executable(${BABEL_BINARY}  ${PACKAGES_HEADER_FILES} ${PACKAGES_SOURCE_FILES})


# 链接 RTTR 库
target_link_libraries(${BABEL_BINARY} ${BABEL_RTTR_CORE})

# =================cppbabel END===============================


# =================cppbabel_lib START===============================
# 生成链接库文件
# 为了让单元测试的时候src下的代码能被作为静态链接库使用
add_library(${BABEL_BINARY_LIB} STATIC ${PACKAGES_HEADER_FILES} ${PACKAGES_SOURCE_FILES})
# 链接 RTTR 库
target_link_libraries(${BABEL_BINARY_LIB} ${BABEL_RTTR_CORE})
# =================cppbabel_lib END===============================