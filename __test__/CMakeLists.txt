# set(BINARY ${CMAKE_PROJECT_NAME}_tst)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${BABEL_BINARY_TEST} ${TEST_SOURCES})

add_test(NAME ${BABEL_BINARY_TEST} COMMAND ${BABEL_BINARY_TEST})

# 链接packages生成的lib库和gtest库
target_link_libraries(${BABEL_BINARY_TEST} PUBLIC ${BABEL_BINARY_LIB} gtest)
# target_link_libraries(${BABEL_BINARY_TEST} PUBLIC  gtest)