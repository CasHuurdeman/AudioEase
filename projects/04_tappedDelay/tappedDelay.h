//
// Created by cashu on 04/11/2025.
//

#pragma once

#include "circularBuffer.h"
#include <vector>
#include "testSignal.h"
#include "smoothe.h"
using std::vector;

class TappedDelay {
public:
   TappedDelay() = default;
   TappedDelay(float samplesDelay);
   TappedDelay(float samplesDelay, float feedback);
   TappedDelay(float samplesDelay, float feedback, int bufferSize);
   ~TappedDelay();

   float process(float input, int numSamplesLeft);

   void setFeedback(float feedback);
   void setSamplesDelay(int readHeadIndex, float samplesDelay);
   void setBypass(bool bypassOn);
   void setTargetSamplesDelay(int readHeadIndex, float samplesDelay)
         { m_circularBuffer->setTargetSamplesDelay(readHeadIndex, samplesDelay); }

   float getFeedback() const { return m_feedback; }
   vector<float> getSamplesDelay() const { return m_circularBuffer->getSamplesDelay(); }
   float getBypassStatus() const { return m_bypassOn; }


   void addDelayLine(float samplesDelay) { m_circularBuffer->addReadHead(samplesDelay); }

   void removeDelayLine(int readHeadIndex) { m_circularBuffer->removeReadHead(readHeadIndex); }

private:
   CircularBuffer* m_circularBuffer;
   TestSignal signal;

   bool m_bypassOn = false;
   float m_feedback = 0.0f;
};