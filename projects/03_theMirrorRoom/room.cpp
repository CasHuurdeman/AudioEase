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
  calculateMirrorSources(7);
  calculateReflections();
}

Room::~Room()
{
//	std::cout << "Room - destructor" << std::endl;
}

void Room::calculateReflections()
{
  m_reflections.resize(m_numMirrorSources);
  
  for (int i = 0; i < m_numMirrorSources; i++)
  {
    //Calculate distance from receiver to mirrorSources
    float distance = calculateDistance(m_mirrorSources[i].data(), m_receiver,
      std::size(m_mirrorSources[i]), std::size(m_receiver));
    
    //amplitude according to Richard Moore (Elements of computer music p370)
	  float amplitude = 1 / pow(distance, 1.5f);
    float delayTime = distance / m_soundSpeed * 1000;

    m_reflections[i][0] = delayTime;
    m_reflections[i][1] = amplitude;

    // std::cout << "DelayTime" << i << ": " << m_reflections[i][0] << "\nAmplitude" << i << ": " << m_reflections[i][1] << "\nDistance" << i << ": " << distance << "\n" << std::endl;
  }
}

void Room::calculateMirrorSources(const int diagonalOrder)
{
  //TODO - EXPLANATION!!!!!!!!!!!!!
  std::vector arrX = {m_source[X]};
  std::vector arrY = {m_source[Y]};

  int a = -1;
  //calculate the different X and Y values to be used
  for (int i = 1; i <= diagonalOrder; i++)
  {
    arrX.push_back(static_cast<float>(i) * m_roomDimensions[X] + static_cast<float>(a) * m_source[X]);
    arrX.push_back(static_cast<float>(-i) * m_roomDimensions[X] + static_cast<float>(a) * m_source[X]);
    arrY.push_back(static_cast<float>(i) * m_roomDimensions[Y] + static_cast<float>(a) * m_source[Y]);
    arrY.push_back(static_cast<float>(-i) * m_roomDimensions[Y] + static_cast<float>(a) * m_source[Y]);
    a *= -1;
  }

  //Combine all X and Y values to get the coordinates
  for (float & j : arrX)
  {
    for (float & k : arrY)
    {
      m_mirrorSources.push_back({j, k});
    }
  }

  //delete the m_source coordinate
  m_mirrorSources.erase(m_mirrorSources.begin());

  //save numMirrorSources
  m_numMirrorSources = static_cast<int>(m_mirrorSources.size());
}

float Room::calculateDistance(float coordinatesA[], float coordinatesB[], size_t sizeA, size_t sizeB) {
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

//TODO - createRoom() has no need now
// void Room::createRoom()
// {
//   //Array with coordinates of the corners
//   std::array< std::array<float,2> ,4> m_roomCorners;
//   //topLeft
//   m_roomCorners[topL] =  {-m_roomDimensions[X]/2.0f, m_roomDimensions[Y]/2.0f};
//   //topRight
//   m_roomCorners[topR] =  {m_roomDimensions[X]/2.0f, m_roomDimensions[Y]/2.0f};
//   //bottomRight
//   m_roomCorners[bottomR] =  {m_roomDimensions[X]/2.0f, -m_roomDimensions[Y]/2.0f};
//   //bottomLeft
//   m_roomCorners[bottomL] =  {-m_roomDimensions[X]/2.0f, -m_roomDimensions[Y]/2.0f};
// }

// // Print coordinates
// int size = 4;
// std::cout << "{";
// for (int i = 0; i < size; i++)
// {
//   std::cout << "{";
//
//   for (int j = 0; j < 2; j++)
//   {
//     std::cout << m_mirrorSources[i][j];
//     if (j==0){std::cout << ", ";}
//   }
//
//   if (i != size - 1){std::cout << "}, ";}
//   else std::cout << "}";
// }
// std::cout << "}\n" << std::endl;
