#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p),
        m_xyPad(processorRef.getApvts().getParameter("SoundSourceX"), processorRef.getApvts().getParameter("SoundSourceY"),
                    processorRef.getApvts().getParameter("CircleMidX"),
                    processorRef.getApvts().getParameter("CircleMidY"),
                    processorRef.getApvts().getParameter("RECEIVERDISTANCE")),
        m_ears(processorRef.getApvts().getParameter("RECEIVERDISTANCE")),
        m_snapXTo0(processorRef.getApvts().getParameter("CircleMidX"), "Snap X to 0"),
        m_snapYTo1(processorRef.getApvts().getParameter("CircleMidY"), "Snap Y to 1")

{
    juce::ignoreUnused (processorRef);

//Connecting the sliderAttachments to the sliders
    m_circleOnAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(processorRef.getApvts(), "CircleOn", m_CircleOn);
    // m_normaliseAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(processorRef.getApvts(), "NORMALISE", m_normalise);
    m_radiusXSliderAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.getApvts(), "RADIUSX", m_radiusXSlider);
    m_radiusYSliderAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.getApvts(), "RADIUSY", m_radiusYSlider);
    m_numReflectionsAttach = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(processorRef.getApvts(), "REFLECTIONS", m_numReflections);
    m_speedSliderAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.getApvts(), "SPEED", m_speedSlider);
    m_backOffAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(processorRef.getApvts(), "DIRECTBACKOFF", m_backOff);
    m_convolutionOnAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(processorRef.getApvts(), "CONVOLUTIONON", m_convolutionOn);
    m_convolutionAmpAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.getApvts(), "CONVOLUTIONAMP", m_convolutionAmpSlider);
    m_ZaxisOnAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(processorRef.getApvts(), "ZAXISON", m_ZaxisOn);

    m_earlyReflectionsOnAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(processorRef.getApvts(), "EARLYREFLECTIONS", m_earlyReflectionsOn);
//===============================================XYPAD=================================================
    addAndMakeVisible(m_xyPad);

//===========================================Button=======================================================
    m_CircleOn.setButtonText("Ellipse");
    m_CircleOn.setClickingTogglesState(true);
    m_CircleOn.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::green);
    m_CircleOn.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::red);
    addAndMakeVisible(m_CircleOn);


    // m_normalise.setButtonText("Normalise");
    // m_normalise.setTooltip("Normalises the amplitude of the source and all reflections with it.\nFor when you don't want your original level to change.");
    // m_normalise.setClickingTogglesState(true);
    // m_normalise.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::green);
    // m_normalise.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::red);
    // addAndMakeVisible(m_normalise);

    m_backOff.setButtonText("Back off");
    m_backOff.setTooltip("Turns off the direct sound when the source is on the backside");
    m_backOff.setClickingTogglesState(true);
    m_backOff.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::green);
    m_backOff.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::red);
    addAndMakeVisible(m_backOff);

    m_convolutionOn.setButtonText("Convolution");
    m_convolutionOn.setClickingTogglesState(true);
    m_convolutionOn.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::green);
    m_convolutionOn.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::red);
    addAndMakeVisible(m_convolutionOn);

    m_earlyReflectionsOn.setButtonText("Early Reflections");
    m_earlyReflectionsOn.setClickingTogglesState(true);
    m_earlyReflectionsOn.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::green);
    m_earlyReflectionsOn.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::red);
    addAndMakeVisible(m_earlyReflectionsOn);


    addAndMakeVisible(m_snapXTo0.button);
    m_snapXTo0.button.onClick = [this]() {
        //TODO - find what this value should be
        m_snapXTo0.buttonAttachment.setValueAsCompleteGesture(0); //why 0.3f? --> look in room.changereceivers()
    };
    addAndMakeVisible(m_snapYTo1.button);
    m_snapYTo1.button.onClick = [this]() {
        m_snapYTo1.buttonAttachment.setValueAsCompleteGesture(-1);
    };

    m_ZaxisOn.setButtonText("3D-sound");
    m_ZaxisOn.setClickingTogglesState(true);
    m_ZaxisOn.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::green);
    m_ZaxisOn.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::red);
    addAndMakeVisible(m_ZaxisOn);

//===========================================Sliders===================================================
    m_radiusXSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    m_radiusXSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::steelblue);
    addAndMakeVisible(m_radiusXSlider);

    m_radiusYSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    m_radiusYSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::steelblue);
    addAndMakeVisible(m_radiusYSlider);


    //TODO - I dont like the combobox
    juce::StringArray choices = {"0", "52", "248", "684", "1456", "2660"};
    m_numReflections.addItemList(choices, 1);
    m_numReflections.setSelectedId(3);
    addAndMakeVisible(m_numReflections);

    //Listener distance
    addAndMakeVisible(m_ears.slider);
    m_ears.slider.onValueChange = [this]() { repaint(); };

    //speed slider
    m_speedSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    m_speedSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::steelblue);
    addAndMakeVisible(m_speedSlider);

    m_convolutionAmpSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    m_convolutionAmpSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::steelblue);
    addAndMakeVisible(m_convolutionAmpSlider);


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
    m_numReflectionsLabel.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::steelblue);
    m_numReflectionsLabel.setTooltip("Adds more reflections exponentially.\n (numReflections formula: -1 + (1 + 2n)^2)");
    addAndMakeVisible(m_numReflectionsLabel);

//Ears
    m_earsLabel.setButtonText("Speaker distance");
    m_earsLabel.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::steelblue);
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

//CONVOLUTIONAMP label
    m_convolutionAmpLabel.setButtonText("Convolution amplitude");
    m_convolutionAmpLabel.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::steelblue);
    addAndMakeVisible(m_convolutionAmpLabel);

//RoomSize Label
    m_roomSizeLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    addAndMakeVisible(m_roomSizeLabel);

//signature
    m_myLabel.setFont(17.0f);
    m_myLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::steelblue);
    addAndMakeVisible(m_myLabel);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (610, 600);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

//========================Draw ears=========================================
    // g.setColour (juce::Colours::white);
    //
    // float n = 400/10;  //TODO - roomsize //TODO - 400 is also hardcoded, maybe smth with denormalise? idk
    // float a = 3;
    //
    // float x = m_ears.slider.getValue()/2 * n;
    // float y = 0.01;
    //
    // float xPos =  m_xyPad.getBounds().getCentreX() + x;
    // float yPos =  m_xyPad.getBounds().getCentreY() + y;
    // g.fillEllipse(xPos - a,yPos - a, 2*a, 2*a);
    //
    // xPos =  m_xyPad.getBounds().getCentreX() - x;
    // yPos =  m_xyPad.getBounds().getCentreY() + y;
    // g.fillEllipse(xPos - a,yPos - a, 2*a, 2*a);
}


void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor.

    m_xyPad.setBounds(200,25, 400, 400);

    m_CircleOn.setBounds(10, 30, 80, 35);
    m_backOff.setBounds(110, 30, 80, 35);
    // m_normalise.setBounds(110, 30, 80, 35);

    m_speedLabel.setBounds(10, 95, 100, 20);
    m_speedSlider.setBounds(10, 125, 180, 20);

    m_radiusYLabel.setBounds(10, 155, 100, 20);
    m_radiusYSlider.setBounds(10, 185, 180, 20);

    m_radiusXLabel.setBounds(10, 215, 100, 20);
    m_radiusXSlider.setBounds(10, 245, 180, 20);

    m_earsLabel.setBounds(10,300,100,20);
    m_ears.slider.setBounds(10, 330, 180, 20);

    m_numReflectionsLabel.setBounds(10, 360, 100, 20);
    m_numReflections.setBounds(20, 390, 80, 20);

    m_ZaxisOn.setBounds(10, 430, 100, 20);

    m_myLabel.setBounds(10, getHeight() - 30, 180, 30);
    m_roomSizeLabel.setBounds(600 - 110, 400, 100, 20);


    m_earlyReflectionsOn.setBounds(210, 440, 80, 35);
    m_convolutionOn.setBounds(310, 440, 80, 35);
    m_snapXTo0.button.setBounds(410, 440,80,35);
    m_snapYTo1.button.setBounds(510, 440,80,35);

    m_convolutionAmpLabel.setBounds(210, 510, 80, 40);
    m_convolutionAmpSlider.setBounds(310, 520, 180, 20);
}
