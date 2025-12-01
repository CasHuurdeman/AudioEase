cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)

project(plot VERSION 0.0.1)


juce_add_console_app(plot
    PRODUCT_NAME "Console App Example")

set(DIR ../03_theMirrorRoom)

target_sources(plot PRIVATE

        ${DIR}/reflectionManager.cpp
        ${DIR}/circularBuffer.cpp
#        ${DIR}/tappedDelay.cpp
        ${DIR}/room.cpp
        ${DIR}/receiver.cpp
        main.cpp)


target_compile_definitions(plot
    PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_console_app` call
        JUCE_USE_CURL=0
        SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
)    # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_console_app` call

target_link_libraries(plot
    PRIVATE
        myLibrary
        # ConsoleAppData            # If you'd created a binary data target, you'd link to it here
        juce::juce_core
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags)
