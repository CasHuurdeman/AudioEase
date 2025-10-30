//
// Created by cashu on 29/10/2025.
//

#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class Sine {
public:
    Sine();
    ~Sine();

    void prepare(double sampleRate);
    void process (float* output, const int numSamples);

    float getAmplitude() const { return m_amplitude; }
    float getFrequency() const { return m_frequency; }

    void setAmplitude(const float amplitude) { m_amplitude = amplitude; }
    void setFrequency(const float frequency) { m_frequency = frequency; }

private:
    float m_amplitude = 0.2f;
    float m_frequency = 440.0f;
    float m_sampleRate = 0.0f;
    float m_timeIncrement = 0.0f;
    float m_currentTime = 0.0f;
    double m_twoPi = 2.0 * atan(1);

};

