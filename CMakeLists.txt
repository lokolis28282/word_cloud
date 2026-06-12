cmake_minimum_required(VERSION 3.16)
project(wc)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

find_package(Qt6 REQUIRED COMPONENTS Core Gui)
find_package(GTest REQUIRED)

add_executable(wordcloud src/wordcloud.cpp)
target_link_libraries(wordcloud Qt6::Core Qt6::Gui)

add_executable(test_wordcloud tests/test_wordcloud.cpp src/wordcloud.cpp)
target_compile_definitions(test_wordcloud PRIVATE WORDCLOUD_TESTS)
target_link_libraries(test_wordcloud Qt6::Core Qt6::Gui GTest::gtest)

enable_testing()
add_test(NAME test_wordcloud COMMAND test_wordcloud)
