#pragma once

#include "PluginProcessor.h"
#include "customComp.h"
using std::unique_ptr;
//==============================================================================
class AudioPluginAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    typedef juce::AudioProcessorValueTreeState APVTS;

    unique_ptr<APVTS::SliderAttachment> m_xCoordinateAttachment;
    unique_ptr<APVTS::SliderAttachment> m_yCoordinateAttachment;

    juce::Slider m_xCoordinateSlider;
    juce::Slider m_yCoordinateSlider;


    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
