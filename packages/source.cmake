# 指定文件夹内所有*.h *.cpp文件
# file(GLOB_RECURSE PACKAGES_SOURCES LIST_DIRECTORIES true *.h *.cpp)
# set(SOURCES ${PACKAGES_SOURCES})

set(PACKAGES_HEADER_FILES babel-types/utils.h
                          babel-types/ast_macro.h
                          babel-types/ast.h
                          babel-types/reflect.h
                          babel-log/ylog.h
                          babel-log/log.h
                          babel-shared/any_map.h
                          babel-parser/util_utf8.h
                          )

set(PACKAGES_SOURCE_FILES main.cpp 
                          babel-types/utils.cpp
                          babel-types/reflect.cpp
                          babel-types/var.cpp
                          )