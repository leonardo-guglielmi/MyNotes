# adding gtest
add_subdirectory(./googletest)
set(GTEST_SRC_DIR ./googletest-master/)
include_directories(${GTEST_SRC_DIR}/include ${GTEST_SRC_DIR})

set(TEST_SRC RunAllTest.cpp
        CollectionTest.cpp
        CollectionManagerTest.cpp)
add_executable(runAllTest ${TEST_SRC})
target_link_libraries(runAllTest gtest gtest_main core)
