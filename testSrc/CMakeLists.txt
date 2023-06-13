add_library(testSources OBJECT test.cpp)
target_link_libraries(testSources PRIVATE Catch2::Catch2)