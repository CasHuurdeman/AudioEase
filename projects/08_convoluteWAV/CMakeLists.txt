cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)

project(08_convoluteWAV VERSION 0.0.1)


juce_add_console_app(08_convoluteWAV
    PRODUCT_NAME "Console App Example")

#set(DIR ../04_tappedDelay)

target_sources(08_convoluteWAV PRIVATE
        main.cpp
)


target_compile_definitions(08_convoluteWAV
    PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_console_app` call
        JUCE_USE_CURL=0
        SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
)    # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_console_app` call

 juce_generate_juce_header(08_convoluteWAV)

target_link_libraries(08_convoluteWAV
    PRIVATE
        myLibrary
        # ConsoleAppData            # If you'd created a binary data target, you'd link to it here
        juce::juce_core
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags)
