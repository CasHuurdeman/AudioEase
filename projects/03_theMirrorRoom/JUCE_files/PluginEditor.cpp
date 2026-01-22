#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p),
        m_xyPad(processorRef.getApvts().getParameter("SoundSourceX"), processorRef.getApvts().getParameter("SoundSourceY"),
                    processorRef.getApvts().getParameter("CircleMidX"),
                    processorRef.getApvts().getParameter("CircleMidY")),
        m_ears(processorRef.getApvts().getParameter("RECEIVERDISTANCE"))
{
    juce::ignoreUnused (processorRef);

//Connecting the sliderAttachments to the sliders
    m_circleOnAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(processorRef.getApvts(), "CircleOn", m_CircleOn);
    m_normaliseAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(processorRef.getApvts(), "NORMALISE", m_normalise);
    m_radiusXSliderAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.getApvts(), "RADIUSX", m_radiusXSlider);
    m_radiusYSliderAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.getApvts(), "RADIUSY", m_radiusYSlider);
    m_numReflectionsAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.getApvts(), "REFLECTIONS", m_numReflections);
    m_speedSliderAttach= std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.getApvts(), "SPEED", m_speedSlider);

//===============================================XYPAD=================================================
    addAndMakeVisible(m_xyPad);

//===========================================Button=======================================================
    m_CircleOn.setButtonText("Ellipse");
    m_CircleOn.setClickingTogglesState(true);
    m_CircleOn.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::green);
    m_CircleOn.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::red);
    addAndMakeVisible(m_CircleOn);


    m_normalise.setButtonText("Normalise");
    m_normalise.setTooltip("Normalises the amplitude of the source and all reflections with it.\nFor when you don't want your original level to change.");
    m_normalise.setClickingTogglesState(true);
    m_normalise.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::green);
    m_normalise.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::red);
    addAndMakeVisible(m_normalise);

//===========================================Sliders===================================================
    m_radiusXSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    m_radiusXSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::steelblue);
    addAndMakeVisible(m_radiusXSlider);

    m_radiusYSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    m_radiusYSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::steelblue);
    addAndMakeVisible(m_radiusYSlider);

    //NumRefelctions
    m_numReflections.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    m_numReflections.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::steelblue);
    addAndMakeVisible(m_numReflections);

    //Listener distance
    addAndMakeVisible(m_ears.slider);
    m_ears.slider.onValueChange = [this]() { repaint(); };

    //speed slider
    m_speedSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    m_speedSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::steelblue);
    addAndMakeVisible(m_speedSlider);


//==========================================LABELS====================================================
    m_radiusXLabel.setButtonText("Circle X");
    m_radiusXLabel.setToggleState(true, juce::NotificationType::dontSendNotification);
    m_radiusXLabel.setClickingTogglesState(true);
    m_radiusXLabel.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::darkred);
    m_radiusXLabel.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::darkred);
    addAndMakeVisible(m_radiusXLabel);

    //LAMBDA FUNCTION
    m_radiusXLabel.onClick = [this]() {
        //change state of the button when clicked
        const bool click = m_radiusXLabel.getToggleState();
        m_radiusXLabel.setButtonText(click ? "Circle X" : "(circle width)");
    };

//RadiusYLabel
    m_radiusYLabel.setButtonText("Circle Y");
    m_radiusYLabel.setToggleState(true, juce::NotificationType::dontSendNotification);
    m_radiusYLabel.setClickingTogglesState(true);
    m_radiusYLabel.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::darkred);
    m_radiusYLabel.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::darkred);
    addAndMakeVisible(m_radiusYLabel);

    //LAMBDA FUNCTION
    m_radiusYLabel.onClick = [this]() {
        //change state of the button when clicked
        const bool click = m_radiusYLabel.getToggleState();
        m_radiusYLabel.setButtonText(click ? "Circle Y" : "(circle height)");
    };


//NumReflections
    m_numReflectionsLabel.setButtonText("Num reflections");
    m_numReflectionsLabel.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::darkred);
    m_numReflectionsLabel.setTooltip("Adds more reflections exponentially.\n (numReflections formula: -1 + (1 + 2n)^2)");
    addAndMakeVisible(m_numReflectionsLabel);

//Ears
    m_earsLabel.setButtonText("Speaker distance");
    m_earsLabel.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::darkred);
    addAndMakeVisible(m_earsLabel);

//speedslider
    m_speedLabel.setButtonText("Speed");
    m_speedLabel.setToggleState(true, juce::NotificationType::dontSendNotification);
    m_speedLabel.setClickingTogglesState(true);
    m_speedLabel.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::darkred);
    m_speedLabel.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::darkred);
    addAndMakeVisible(m_speedLabel);

    //LAMBDA FUNCTION
    m_speedLabel.onClick = [this]() {
        //change state of the button when clicked
        const bool click = m_speedLabel.getToggleState();
        m_speedLabel.setButtonText(click ? "Speed" : "Sorry, a bit buggy");
    };

//signature
    m_myLabel.setFont(17.0f);
    m_myLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::steelblue);
    addAndMakeVisible(m_myLabel);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (610, 450);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // g.setColour (juce::Colours::midnightblue);
    // g.setFont (17.0f);
    // g.drawFittedText("by Cas Huurdeman", 10, getHeight() - 30, 190, 40, juce::Justification::left, 1);

//========================Draw ears=========================================
    g.setColour (juce::Colours::white);

    float n = 400/20;
    float a = 3;

    float x = m_ears.slider.getValue()/2 * n;
    float y = 0.01;

    float xPos =  m_xyPad.getBounds().getCentreX() + x;
    float yPos =  m_xyPad.getBounds().getCentreY() + y;
    g.fillEllipse(xPos - a,yPos - a, 2*a, 2*a);

    xPos =  m_xyPad.getBounds().getCentreX() - x;
    yPos =  m_xyPad.getBounds().getCentreY() + y;
    g.fillEllipse(xPos - a,yPos - a, 2*a, 2*a);
}


void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor.

    m_xyPad.setBounds(200,25, 400, 400);

    m_CircleOn.setBounds(10, 30, 80, 35);
    m_normalise.setBounds(110, 30, 80, 35);

    m_speedLabel.setBounds(10, 95, 100, 20);
    m_speedSlider.setBounds(10, 125, 180, 20);

    m_radiusYLabel.setBounds(10, 155, 100, 20);
    m_radiusYSlider.setBounds(10, 185, 180, 20);

    m_radiusXLabel.setBounds(10, 215, 100, 20);
    m_radiusXSlider.setBounds(10, 245, 180, 20);

    m_numReflectionsLabel.setBounds(10,300,100,20);
    m_numReflections.setBounds(10, 330, 180, 20);

    m_earsLabel.setBounds(10, 360, 100, 20);
    m_ears.slider.setBounds(10, 390, 180, 20);

    m_myLabel.setBounds(10, getHeight() - 30, 180, 30);
}
