# header only files need INTERFACE
add_library(audio_header INTERFACE)
target_include_directories(audio_header INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        /dspMath.h,
        /pulse.h,
        /writeToFile.h,
        /customPrint.h
        /calculateDistance.h
        /speedTest.h
        /readWAV.h
        /binFile.h
)

add_library(myLibrary STATIC interpolation.cpp writeToWAV.cpp)
target_compile_features(myLibrary PUBLIC cxx_std_20)
target_include_directories(myLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})