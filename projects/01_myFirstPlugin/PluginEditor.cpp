#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);

    m_freqSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.getApvts(), "FREQUENCY", m_frequencySlider);
    m_bypassButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(processorRef.getApvts(), "BYPASS", m_bypassButton);

    //enums in Slider class
    m_frequencySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    m_frequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(m_frequencySlider);

    m_bypassButton.setButtonText("Bypassed");
    m_bypassButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    m_bypassButton.setClickingTogglesState(true);
    m_bypassButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::red);
    m_bypassButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::green);
    addAndMakeVisible(m_bypassButton);

    //LAMBDA FUNCTION
    m_bypassButton.onClick = [this]() {
       //change state of the button when clicked
        const bool bypassed = m_bypassButton.getToggleState();
        m_bypassButton.setButtonText(bypassed ? "Bypassed" : "Bypass");
    };

    m_frequencyLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(m_frequencyLabel);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 400);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));



    // g.setColour (juce::Colours::white);
    // g.setFont (15.0f);
    // g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // There are multiple ways to position the components, so check out what works best on the website

    m_frequencySlider.setBounds(getWidth() / 2 - 50, getHeight() / 2 - 100, 100, 200);
    m_bypassButton.setBounds(getWidth() / 2 - 50, getHeight() / 2 + 120, 100, 20);
    m_frequencyLabel.setBounds(getWidth() / 2 - 50, getHeight() / 2 - 120, 100, 20);
}
