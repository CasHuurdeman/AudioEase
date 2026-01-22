#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "../reflectionManager.h"
#include "customComp.h"
#include "testSignal.h"
#include "speedTest.h"

//==============================================================================
class AudioPluginAudioProcessor final : public juce::AudioProcessor
{
public:
    //==============================================================================
    AudioPluginAudioProcessor();
    ~AudioPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    using AudioProcessor::processBlock;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState& getApvts(){ return m_apvts; }
    ReflectionManager*& getReflectionManager() {return m_reflectionManager; }


private:
    //TODO - dont forget to delete; is this needed?
    ReflectionManager* m_reflectionManager;
    TestSignal m_sine;
    TestSignal m_cosine;


    juce::AudioProcessorValueTreeState m_apvts;

    std::atomic<float>* m_xCoordinate;
    std::atomic<float>* m_yCoordinate;
    std::atomic<float>* m_CircleOn;
    std::atomic<float>* m_radiusX;
    std::atomic<float>* m_radiusY;
    std::atomic<float>* m_diagonalOrder;
    std::atomic<float>* m_normalise;
    std::atomic<float>* m_receiverDistance;
    std::atomic<float>* m_speed;


    ParameterListener m_parameterListenerX;
    ParameterListener m_parameterListenerY;

    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessor)
};
