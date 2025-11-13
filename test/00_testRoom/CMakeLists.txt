cmake_minimum_required(VERSION 3.22)


project(00_testRoom VERSION 0.0.1)


juce_add_console_app(00_testRoom
    PRODUCT_NAME "Console App Example")

target_sources(00_testRoom PRIVATE
        reflectionManager.cpp
        circularBuffer.cpp
        delay.cpp
        grid.cpp
        main.cpp)


target_compile_definitions(00_testRoom
    PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_console_app` call
        JUCE_USE_CURL=0)    # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_console_app` call

target_link_libraries(00_testRoom
    PRIVATE
        myLibrary
        # ConsoleAppData            # If you'd created a binary data target, you'd link to it here
        juce::juce_core
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags)
