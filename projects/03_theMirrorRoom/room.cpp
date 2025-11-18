//
// Created by cashu on 11/11/2025.
//

#include "room.h"
#include <iostream>

Room::Room()
{
//  std::cout << "Room - constructor" << std::endl;

  //calculate amplitude from source to receiver
  float distance = calculateDistance(m_source, m_receiver, std::size(m_source), std::size(m_receiver));
  m_sourceAmplitude = 1 / pow(distance, 1.5f);

  // std::cout << "Distance: " << distance << "SourceAmplitude: " << getSourceAmplitude() << "\n" << std::endl;

  createRoom();
  calculateMirrorSources();
  calculateReflections();
}

Room::~Room()
{
//	std::cout << "Room - destructor" << std::endl;
}

void Room::calculateReflections()
{
  //c = sound of speed in m/s @20 deg celcius
  float c = 343.0f;

  m_reflections.resize(m_numMirrorSources);
  
  for (int i = 0; i < m_numMirrorSources; i++)
  {
    //Calculate distance from receiver to mirrorSources
    float distance = calculateDistance(m_mirrorSources[i].data(), m_receiver,
      std::size(m_mirrorSources[i]), std::size(m_receiver));
    
    //amplitude according to Richard Moore (Elements of computer music p370)
	  float amplitude = 1 / pow(distance, 1.5f);
    float delayTime = distance / c * 1000;

    m_reflections[i][0] = delayTime;
    m_reflections[i][1] = amplitude;

    // std::cout << "DelayTime" << i << ": " << m_reflections[i][0] << "\nAmplitude" << i << ": " << m_reflections[i][1] << "\nDistance" << i << ": " << distance << "\n" << std::endl;
  }
}

void Room::createRoom()
{
  //topLeft
  m_roomCorners[topL] =  {-roomDimensions[X]/2.0f, roomDimensions[Y]/2.0f};
  //topRight
  m_roomCorners[topR] =  {roomDimensions[X]/2.0f, roomDimensions[Y]/2.0f};
  //bottomRight
  m_roomCorners[bottomR] =  {roomDimensions[X]/2.0f, -roomDimensions[Y]/2.0f};
  //bottomLeft
  m_roomCorners[bottomL] =  {-roomDimensions[X]/2.0f, -roomDimensions[Y]/2.0f};

  // //Print the coordinates
  // std::cout << "{";
  // for (int i = 0; i < 4; i++)
  //   {
  //   std::cout << "{";
  //
  //   for (int j = 0; j < 2; j++)
  //   {
  //     std::cout << m_roomCorners[i][j];
  //     if (j==0){std::cout << ", ";}
  //   }
  //
  //   if (i != 3){std::cout << "}, ";}
  //   else std::cout << "}";
  //   }
  // std::cout << "}" << std::endl;
}

void Room::calculateMirrorSources()
{

  float source1RX = roomDimensions[X] - m_source[X];
  float source1RY = m_source[Y];
  std::array<float, 2> mirrorSource1R{source1RX, source1RY};

  float source1LX = -roomDimensions[X] - m_source[X];
  float source1LY = m_source[Y];
  std::array<float, 2> mirrorSource1L{source1LX, source1LY};

  float source1TX = m_source[X];
  float source1TY = roomDimensions[Y] - m_source[Y];
  std::array<float, 2> mirrorSource1T{source1TX, source1TY};

  float source1BX = m_source[X];
  float source1BY = -roomDimensions[Y] - m_source[Y];
  std::array<float, 2> mirrorSource1B{source1BX, source1BY};

  m_mirrorSources.resize(4);
  m_mirrorSources[0] = mirrorSource1R;
  m_mirrorSources[1] = mirrorSource1L;
  m_mirrorSources[2] = mirrorSource1T;
  m_mirrorSources[3] = mirrorSource1B;

  m_numMirrorSources = static_cast<int>(m_mirrorSources.size());
  // // Print the coordinates
  //  std::cout << "Mirror Sources: {";
  //  for (int i = 0; i < 4; i++)
  //  {
  //    std::cout << "{";
  //
  //    for (int j = 0; j < 2; j++)
  //    {
  //      std::cout << m_mirrorSources[i][j];
  //      if (j==0){std::cout << ", ";}
  //    }
  //
  //    if (i != 3){std::cout << "}, ";}
  //    else std::cout << "}";
  //  }
  //  std::cout << "}\n" << std::endl;
}

float Room::calculateDistance(float coordinatesA[], float coordinatesB[], int sizeA, int sizeB) {
  //manage array sizes
  int arraySize;
  if (sizeA < sizeB) arraySize = sizeA;
  else arraySize = sizeB;

  float value = 0;
  for (int i = 0; i < arraySize; i++)
  {
    value += square(coordinatesA[i] - coordinatesB[i]);
  }

  return sqrt(value);
}

