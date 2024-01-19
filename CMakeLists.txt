project(5eCharacterTool)

cmake_minimum_required(VERSION 3.16)
find_package(Catch2 REQUIRED)

add_subdirectory(src)
add_subdirectory(testSrc)

add_executable(tests test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain testSources)

add_executable(menu characterMenu.cpp)
target_link_libraries(menu character)