//
// Created by cashu on 29/10/2025.
//

#include "sine.h"
#include <iostream>

Sine::Sine(){
  std::cout << "Sine - constructor" << std::endl;
}

Sine::~Sine(){
  std::cout << "Sine - destructor" << std::endl;
}

void Sine::prepare(double sampleRate) {
    //juce werkt met doouble samplerate, maar in de process functie willen we met float samplerate werken
    m_sampleRate =  static_cast<float>(sampleRate);
    m_timeIncrement = 1.0f / m_sampleRate;
}

void Sine::process (float* output, const int numSamples){

    for (int sample = 0; sample < numSamples; ++sample) {
        output[sample] = m_amplitude * sin(m_twoPi * m_frequency * m_currentTime);
        m_currentTime += m_timeIncrement;
    }
}