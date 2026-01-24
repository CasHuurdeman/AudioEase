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

    unique_ptr<APVTS::ButtonAttachment> m_circleOnAttach;
    juce::TextButton m_CircleOn;

    unique_ptr<APVTS::ButtonAttachment> m_normaliseAttach;
    juce::TextButton m_normalise;

    unique_ptr<APVTS::ButtonAttachment>  m_backOffAttach;
    juce::TextButton m_backOff;

    juce::TextButton  m_radiusXLabel;
    unique_ptr<APVTS::SliderAttachment> m_radiusXSliderAttach;
    juce::Slider m_radiusXSlider;

    juce::TextButton m_radiusYLabel;
    unique_ptr<APVTS::SliderAttachment> m_radiusYSliderAttach;
    juce::Slider m_radiusYSlider;

    juce::TextButton  m_numReflectionsLabel;
    unique_ptr<APVTS::SliderAttachment> m_numReflectionsAttach;
    juce::Slider m_numReflections;

    juce::TextButton  m_speedLabel;
    unique_ptr<APVTS::SliderAttachment> m_speedSliderAttach;
    juce::Slider m_speedSlider;

    juce::Label m_myLabel{"signature", "by Cas Huurdeman"};

    juce::TooltipWindow m_tooltipWindow{nullptr, 200};

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor& processorRef;

    comp::XYPad m_xyPad;
    comp::Ears m_ears;
    juce::TextButton  m_earsLabel;

    comp::CustomButton m_snapXTo0;
    comp::CustomButton m_snapYTo0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
