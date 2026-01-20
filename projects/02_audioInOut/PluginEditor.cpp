#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p),
        m_slider(processorRef.getApvts().getParameter("GAIN")),
        m_xyPad(processorRef.getApvts().getParameter("X"), processorRef.getApvts().getParameter("Y"))
{
    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible(m_Label);
    addAndMakeVisible(m_slider.slider);
    addAndMakeVisible(m_xyPad);

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
    g.drawFittedText ("Nothing happens", getLocalBounds(), juce::Justification::centred, 1);
}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    m_Label.setBounds(0, 0, 100, 20);
    m_xyPad.setBounds(0, 0, 200, 200);
    m_slider.slider.setBounds(0,0, getWidth()/4, getHeight());

}
