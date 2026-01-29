#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "dspMath.h"
#include "readWAV.h"
std::string sourceDir = SOURCE_DIR;

#include "writeToWAV.h"

//==============================================================================
AudioPluginAudioProcessor::AudioPluginAudioProcessor()
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), m_apvts(*this, nullptr, "Parameters", createParameters())
                        ,m_parameterListenerX(getApvts().getParameter("SoundSourceX"))
                        ,m_parameterListenerY(getApvts().getParameter("SoundSourceY"))
{
}

AudioPluginAudioProcessor::~AudioPluginAudioProcessor()
{
}

//==============================================================================
const juce::String AudioPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AudioPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AudioPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AudioPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AudioPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AudioPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AudioPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AudioPluginAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String AudioPluginAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void AudioPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}


//========================== PREPARE AND PROCESS FUNCTIONS ================================

void AudioPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused (sampleRate, samplesPerBlock);

//============================UI================================
//Put the raw parameter value pointers in the variables
    m_xCoordinate = m_apvts.getRawParameterValue("CircleMidX");
    m_yCoordinate = m_apvts.getRawParameterValue("CircleMidY");

    m_CircleOn = m_apvts.getRawParameterValue("CircleOn");
    m_normalise = m_apvts.getRawParameterValue("NORMALISE");

    m_radiusX = m_apvts.getRawParameterValue("RADIUSX");
    m_radiusY = m_apvts.getRawParameterValue("RADIUSY");

    m_diagonalOrder = m_apvts.getRawParameterValue("REFLECTIONS");
    m_receiverDistance = m_apvts.getRawParameterValue("RECEIVERDISTANCE");

    m_speed = m_apvts.getRawParameterValue("SPEED");
    m_directBackOff = m_apvts.getRawParameterValue("DIRECTBACKOFF");

    m_convolutionOn = m_apvts.getRawParameterValue("CONVOLUTIONON");
    m_earlyReflectionsOn = m_apvts.getRawParameterValue("EARLYREFLECTIONS");

//========================================PLUGIN========================================
//Initialise reflectionManager
    m_reflectionManager = new ReflectionManager();
    m_reflectionManager->setNormalise(false); //TODO - here may be more, because I need to calculate some more if I change this
    m_reflectionManager->prepare(static_cast<int>(sampleRate), getTotalNumOutputChannels());

//=========================================================
    m_reflectionManager->changeNumReflections(30);
    //Does this fuck it up?
    // m_reflectionManager->moveSource(0.3f, -1, 1.7f);

    TestSignal pulse1;
    TestSignal pulse2;

    //Max delay (not perfectly, but thats less important than speed):
    int size = m_reflectionManager->getRoom().getReceiver(0)->getReflections().size();
    int maxSamplesDelay = dspMath::msToSamples(m_reflectionManager->getRoom().getReceiver(0)->getReflections()[size - 1][0], sampleRate);

    m_impulseResponseL.resize(maxSamplesDelay);
    m_impulseResponseR.resize(maxSamplesDelay);

    for (int i = 0; i < maxSamplesDelay; i++)
    {
        int numSamplesLeft = static_cast<int>(sampleRate) - i;
        float signalL = m_reflectionManager->process(pulse1.givePulse(), 0, numSamplesLeft);
        float signalR = m_reflectionManager->process(pulse2.givePulse(), 1, numSamplesLeft);

        m_impulseResponseL[i] = signalL;
        m_impulseResponseR[i]= signalR;
    }

    // //========================================CONVOLUTION===============================================
    m_convolutionEngines.resize(2);
    m_inputBuffer.resize(samplesPerBlock, 0);

    m_convolutionEngines[0].prepare(samplesPerBlock, m_impulseResponseL);
    m_convolutionEngines[1].prepare(samplesPerBlock, m_impulseResponseR);

//TODO - is this needed?
//DELETE EARLY REFLECTIONS OUT OF IR
    // for (int i = 0; i < m_convolutionEngines.size(); i++)
    // {
    //     int numSamplesToCut = dspMath::msToSamples(m_reflectionManager->getRoom().getMaxDelay(), getSampleRate());
    //     m_convolutionEngines[i].cutEarlyReflections(numSamplesToCut);
    // }
}

void AudioPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool AudioPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}

void AudioPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages){

    juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    int numSamples = buffer.getNumSamples();

    //Comment
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i) {
        buffer.clear (i, 0, numSamples);
    }



//======================================================UI============================================================

//Load the raw parameter values
    float X = m_xCoordinate->load();
    float Y = m_yCoordinate->load();
    const float Z = 1.7f;

    float circleOn = m_CircleOn->load();
    float normalise = m_normalise->load();
    float radiusX = m_radiusX->load();
    float radiusY = m_radiusY->load();

        //just gets the index, but that exactly what we want now
    float diagonalOrder = m_diagonalOrder->load();
    float receiverDistance = m_receiverDistance->load();

    float speed = m_speed->load();
    bool directBackOff = static_cast<bool>(m_directBackOff->load());
    bool convolutionOn = static_cast<bool>(m_convolutionOn->load());

    bool earlyReflectionsOn = static_cast<bool>(m_earlyReflectionsOn->load());


//Change num reflections
    if (diagonalOrder != m_reflectionManager->getRoom().getDiagonalOrder())
    {
        m_reflectionManager->changeNumReflections(diagonalOrder);

        for (int i = 0; i < m_convolutionEngines.size(); i++)
        {
            auto maxDelay = std::max_element(
                m_reflectionManager->getRoom().getReceiver(i)->getReflections().begin(),
                m_reflectionManager->getRoom().getReceiver(i)->getReflections().end());

            int numSamplesToCut = static_cast<int>(dspMath::msToSamples(maxDelay[0][0], getSampleRate()));
            m_convolutionEngines[i].cutEarlyReflections(numSamplesToCut);
        }
    }

//Change listener distance
     if (receiverDistance != m_reflectionManager->getRoom().getReceiverDistance())
     {
         m_reflectionManager->moveReceivers(receiverDistance);
     }

//Normalise the amplitude or not
    // m_reflectionManager->setNormalise(static_cast<bool>(normalise));
    m_reflectionManager->setNormalise(false);

//MODULATING SIGNAL TO MOVE THE SOURCE
    //TODO - 40 is roomsize*2
    float freq = speed/40;

    int localSampleRate = getSampleRate() / numSamples;
    float cosine = m_cosine.cosine(freq, localSampleRate);
    float sine = m_sine.sine(freq, localSampleRate);

//Source movement
    float posX = X + (cosine) * radiusX * circleOn;
    float posY = Y + (sine) * radiusY * circleOn;
    //-X and -Y or it goes to the wrong side when sliding horizontally haha
    //(because of the way the UI coordinates work)
    m_reflectionManager->moveSource(-posX,-posY,Z);

//Update UI
    m_parameterListenerX.updateValue(posX);
    m_parameterListenerY.updateValue(posY);

//BEHIND HEAD
    if (directBackOff)
    {
        if (posY > 0) getReflectionManager()->turnOffDirectSound(posY*20);
        else getReflectionManager()->turnOnDirectSound();
    }
    else getReflectionManager()->turnOnDirectSound();


    //Buffer loop
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
        auto* output = buffer.getWritePointer(channel);
        auto* input = buffer.getReadPointer(channel);

        memcpy(&m_inputBuffer[0], input, buffer.getNumSamples() * sizeof(float));

        //CONVOLUTION ON/OFF
        if (convolutionOn) m_output = m_convolutionEngines[channel].process(m_inputBuffer);
        else
        {
        m_output.clear();
        m_output.resize(buffer.getNumSamples(), 0);
        }

        // sample loop
         for (int sample = 0; sample < numSamples; ++sample) {
             if (earlyReflectionsOn)
             {
                int numSamplesLeft = numSamples - sample;
                m_output[sample] += m_reflectionManager->process(input[sample], channel, numSamplesLeft);
             }
         }

        memcpy(output, &m_output[0], buffer.getNumSamples() * sizeof(float));
    }
}

//========================= USER INTERFACE PART ==================================
bool AudioPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AudioPluginAudioProcessor::createEditor()
{
    return new AudioPluginAudioProcessorEditor (*this);
}

//========================= SAVE AND LOAD SETTINGS ================================
void AudioPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused (destData);
}

void AudioPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused (data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioPluginAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout AudioPluginAudioProcessor::createParameters() {
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(
        "SoundSourceX",
        "xCoord",
        -10.0f,
        10.0f,
        0.0f ));

    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(
        "SoundSourceY",
        "yCoord",
        -10.0f,
        10.0f,
        0.0f));

    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(
    "CircleMidX",
    "X coordinate of circle middle",
    -10.0f,
    10.0f,
    0.0f));

    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(
    "CircleMidY",
    "Y coordinate of circle middle",
    -10.0f,
    10.0f,
    -1.0f));

    parameters.push_back(std::make_unique<juce::AudioParameterBool>(
    "CircleOn",
    "Circle on",
    0));

    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(
    "RADIUSX",
    "Circle Radius X value",
    0.0f,
    10.0f,
    2.0f));

    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(
    "RADIUSY",
    "Circle Radius Y value",
    0.0f,
    10.0f,
    2.0f));

    juce::StringArray choices = {"0", "52", "248", "684", "1456", "2660"};
    parameters.push_back(std::make_unique<juce::AudioParameterChoice>(
    "REFLECTIONS",
    "Sets the amount of reflections calculated",
    choices,
    2));

    parameters.push_back(std::make_unique<juce::AudioParameterBool>(
    "NORMALISE",
    "Amplitude normalisation on",
    0));

    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(
     "RECEIVERDISTANCE",
     "Distance between 'ears'",
     0.15f,
     19.0f,
     0.17f));

    parameters.push_back(std::make_unique<juce::AudioParameterFloat>(
     "SPEED",
     "Speed of source in m/s",
     1.0f,
     10.0f,
     5.0f));

    parameters.push_back(std::make_unique<juce::AudioParameterBool>(
    "DIRECTBACKOFF",
    "Direct sound off when in the back",
    0));

    parameters.push_back(std::make_unique<juce::AudioParameterBool>(
    "CONVOLUTIONON",
    "Convolution on",
    0));

        parameters.push_back(std::make_unique<juce::AudioParameterBool>(
    "EARLYREFLECTIONS",
    "Early reflections on",
    1));

    return {parameters.begin(), parameters.end()};
}
