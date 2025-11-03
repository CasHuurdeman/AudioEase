//
// Created by cashu on 29/10/2025.
//

#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

//This is not a very pretty sine class, use or make another one when its needed.
//This is just to show how JUCE is done
class Sine {
public:
    Sine();
    ~Sine();

    void prepare(double sampleRate);
    void process (float* output, const int numSamples);

    float getAmplitude() const { return m_amplitude; }
    float getFrequency() { return m_smoothedFreq.getNextValue(); }

    void setAmplitude(const float amplitude) { m_amplitude = amplitude; }
    void setFrequency(const float frequency) { m_smoothedFreq.setTargetValue(frequency); }

private:
    float m_amplitude = 0.4f;
    float m_frequency = 440.0f;
    float m_sampleRate = 0.0f;
    float m_timeIncrement = 0.0f;
    float m_currentTime = 0.0f;
    float m_twoPi = 2.0 * atan(1);

    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Multiplicative> m_smoothedFreq;
};

