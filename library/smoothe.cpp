//
// Created by cashu on 15/12/2025.
//

#include "smoothe.h"

float Smoothe::smootheValue(float value, float targetValue, int numSteps)
{
  if (numSteps <= 0) return value;
  float smoothedValue = value + (targetValue - value)/ numSteps;

  return smoothedValue;
}

//
//float Smoothe::smootheValue(float value)
//{
//    if (posDelta)
//    {
//        if ((m_targetValue - value) <= m_stepSize) {
//            return m_targetValue;
//        }
//        value += m_stepSize;
//        return value;
//    }
//
//    //else
//    if ((m_targetValue - value) > m_stepSize) {
//        return m_targetValue;
//    }
//    value += m_stepSize;
//    return value;
//}
//
//void Smoothe::setTarget(float value, float targetValue, int numSteps) {
//    m_targetValue = targetValue;
//
//    float delta = targetValue - value;
//    m_stepSize = delta / numSteps;
//
//    if (delta < 0) posDelta = false;
//    else posDelta = true;
//}


