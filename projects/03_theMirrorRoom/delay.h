//
// Created by cashu on 04/11/2025.
//

#pragma once
#include "circularBuffer.h"

//TODO - wil ik weer een effect base class?
   //-> bypass, dry/wet (meh), prepare?; nee, maar hoe wil ik het met de bypass doen?
class Delay {
public:
   Delay() = default;
   Delay(float samplesDelay, float feedback);
   Delay(float samplesDelay, float feedback, int bufferSize);
   ~Delay();

   float process(float input);

   void setFeedback(float feedback);
   void setSamplesDelay(float samplesDelay);
   void setBypass(bool bypassOn);

   float getFeedback() const { return m_feedback; }
   float getSamplesDelay() const { return m_circularBuffer->getSamplesDelay(); }
   float getBypassStatus() const { return m_bypassOn; }


private:
   CircularBuffer* m_circularBuffer;

   //heb ik dit uberhaupt nodig in de delay class?
   bool m_bypassOn = false;
   float m_feedback = 0.0f;
};