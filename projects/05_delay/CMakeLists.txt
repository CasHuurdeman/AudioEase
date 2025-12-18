project(05_Delay  VERSION 0.0.1)

juce_add_plugin(05_Delay
        # VERSION ...                               # Set this if the plugin version is different to the project version
        # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
        # ICON_SMALL ...
         COMPANY_NAME Cas                          # Specify the name of the plugin's author
         IS_SYNTH FALSE                       # Is this a synth or an effect?
         NEEDS_MIDI_INPUT FALSE               # Does the plugin need midi input?
         NEEDS_MIDI_OUTPUT FALSE              # Does the plugin need midi output?
         IS_MIDI_EFFECT FALSE                 # Is this plugin a MIDI effect?
         EDITOR_WANTS_KEYBOARD_FOCUS FALSE    # Does the editor need keyboard focus?
         COPY_PLUGIN_AFTER_BUILD FALSE        # Should the plugin be installed to a default location after building?
        PLUGIN_MANUFACTURER_CODE Juce               # A four-character manufacturer id with at least one upper-case character
        PLUGIN_CODE Dem0                            # A unique four-character plugin id with exactly one upper-case character
        # GarageBand 10.3 requires the first letter to be upper-case, and the remaining letters to be lower-case
        FORMATS Standalone VST3                         # The formats to build. Other valid formats are: AAX Unity VST AU AUv3
        PRODUCT_NAME "The Mirror Room"         # The name of the final executable, which can differ from the target name
)

target_sources(05_Delay  PRIVATE
        circularBuffer.cpp
        delay.cpp
        JUCE_files/PluginEditor.cpp
        JUCE_files/PluginProcessor.cpp
)

target_compile_definitions(05_Delay  PRIVATE JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0
        JUCE_IGNORE_VST3_MISMATCHED_PARAMETER_ID_WARNING=1
    SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(05_Delay 
        PRIVATE
        myLibrary
        juce::juce_core
        juce::juce_audio_utils
        juce::juce_audio_devices
        juce::juce_audio_basics
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)