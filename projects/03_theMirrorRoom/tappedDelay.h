//
// Created by cashu on 04/11/2025.
//

#pragma once
#include "circularBuffer.h"
#include <vector>

class TappedDelay {
public:
   TappedDelay() = default;
   TappedDelay(int bufferSize);
   TappedDelay(float samplesDelay, float feedback);
   TappedDelay(float samplesDelay, float feedback, int bufferSize);
   ~TappedDelay();

   float process(float input);

   void setFeedback(float feedback);
   void setSamplesDelay(int readHeadIndex, float samplesDelay);
   void setBypass(bool bypassOn);

   float getFeedback() const { return m_feedback; }
   std::vector<float> getSamplesDelay() const { return m_circularBuffer->getSamplesDelay(); }
   float getBypassStatus() const { return m_bypassOn; }


   void addDelayLine(float samplesDelay) { m_circularBuffer->addReadHead(samplesDelay); }
   void removeDelayLine(int readHeadIndex) { m_circularBuffer->removeReadHead(readHeadIndex); }

private:
   CircularBuffer* m_circularBuffer;

   bool m_bypassOn = false;
   float m_feedback = 0.0f;
};