project(00_cmakeTest VERSION 0.0.1)
juce_add_console_app(00_cmakeTest PRODUCT_NAME "a")

target_sources(a PRIVATE
    main.cpp
)

target_compile_definitions(a PRIVATE JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0
    SOURCE_DIR = "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(a
        PRIVATE
        juce::juce_core
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags

)