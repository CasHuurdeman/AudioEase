//
// Created by cashu on 04/11/2025.
//

#pragma once
#include "circularBuffer.h"

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

   bool m_bypassOn = false;
   float m_feedback = 0.0f;
};