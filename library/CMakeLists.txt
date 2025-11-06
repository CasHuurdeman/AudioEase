
add_library(myLibrary STATIC interpolation.cpp)
target_compile_features(myLibrary PUBLIC cxx_std_20)
target_include_directories(myLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})