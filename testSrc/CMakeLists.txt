add_library(testSources OBJECT characterTest.cpp)
target_link_libraries(testSources PRIVATE Catch2::Catch2 character)