#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);

    //Connecting the sliderattachment to the sliders
    m_xCoordinateAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.getApvts(), "X", m_xCoordinateSlider);
    m_yCoordinateAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.getApvts(), "Y", m_yCoordinateSlider);

    m_xCoordinateSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    m_yCoordinateSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    addAndMakeVisible(m_xCoordinateSlider);
    addAndMakeVisible(m_yCoordinateSlider);


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

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    // g.drawFittedText ("Where am I?\nCan you hear me?", getLocalBounds(), juce::Justification::centred, 1);
}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    m_xCoordinateSlider.setBounds( 15, getHeight() / 2 + 20, 300, 100);
    m_yCoordinateSlider.setBounds(getWidth() / 2 - 80, getHeight() / 2 - 150, 100, 200);

}
