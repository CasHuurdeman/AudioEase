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
  m_roomCorners[topL] =  {-m_roomDimensions[X]/2.0f, m_roomDimensions[Y]/2.0f};
  //topRight
  m_roomCorners[topR] =  {m_roomDimensions[X]/2.0f, m_roomDimensions[Y]/2.0f};
  //bottomRight
  m_roomCorners[bottomR] =  {m_roomDimensions[X]/2.0f, -m_roomDimensions[Y]/2.0f};
  //bottomLeft
  m_roomCorners[bottomL] =  {-m_roomDimensions[X]/2.0f, -m_roomDimensions[Y]/2.0f};
}

void Room::calculateMirrorSources()
{
  // //TODO - can I combine the for loops and/or make it more efficient?
  // //algoritmisch
  int diagonalOrder = 2;
  int a = -1;
  std::vector arrX = {m_source[X]};
  std::vector arrY = {m_source[Y]};

  //calculate the different X and Y values to be used
  for (int i = 1; i <= diagonalOrder; i++)
  {
    arrX.push_back(i * m_roomDimensions[X] + a * m_source[X]);
    arrX.push_back(-i * m_roomDimensions[X] + a * m_source[X]);
    arrY.push_back(i * m_roomDimensions[Y] + a * m_source[Y]);
    arrY.push_back(-i * m_roomDimensions[Y] + a * m_source[Y]);
    a *= -1;
  }

  //Combine all X and Y values to get the coordinates
  for (int j = 0; j < arrX.size(); j++)
  {
    for (int k = 0; k < arrY.size(); k++)
    {
      m_mirrorSources.push_back({arrX[j], arrY[k]});
    }
  }

  //delete the m_source coordinate
  m_mirrorSources.erase(m_mirrorSources.begin());





  // //first order
  // float source1RX = 1 * m_roomDimensions[X] - m_source[X];
  // float source1RY = m_source[Y];
  // m_mirrorSources.push_back({source1RX, source1RY});
  //
  // float source1LX = -1 * m_roomDimensions[X] - m_source[X];
  // float source1LY = m_source[Y];
  // m_mirrorSources.push_back({source1LX, source1LY});
  //
  // float source1TX = m_source[X];
  // float source1TY = 1 *  m_roomDimensions[Y] - m_source[Y];
  // m_mirrorSources.push_back({source1TX, source1TY});
  //
  // float source1BX = m_source[X];
  // float source1BY = -1 * m_roomDimensions[Y] - m_source[Y];
  // m_mirrorSources.push_back({source1BX, source1BY});
  //
  //
  // //second order
  // float source2RRX =  2 * m_roomDimensions[X] + m_source[X];
  // float source2RRY = m_source[Y];
  // m_mirrorSources.push_back({source2RRX, source2RRY});
  //
  // float source2LLX = -2 * m_roomDimensions[X] + m_source[X];
  // float source2LLY = m_source[Y];
  // m_mirrorSources.push_back({source2LLX, source2LLY});
  //
  // float source2TTX = m_source[X];
  // float source2TTY = 2 * m_roomDimensions[Y] + m_source[Y];
  // m_mirrorSources.push_back({source2TTX, source2TTY});
  //
  // float source2BBX = m_source[X];
  // float source2BBY = -2 * m_roomDimensions[Y] + m_source[Y];
  // m_mirrorSources.push_back({source2BBX, source2BBY});
  //
  //
  // float source2RTX = 1 * m_roomDimensions[X] - m_source[X];
  // float source2RTY = 1 * m_roomDimensions[Y] - m_source[Y];
  // m_mirrorSources.push_back({source2RTX, source2RTY});
  //
  // float source2LTX = -1 * m_roomDimensions[X] - m_source[X];
  // float source2LTY = 1 * m_roomDimensions[Y] - m_source[Y];
  // m_mirrorSources.push_back({source2LTX, source2LTY});
  //
  // float source2RBX = 1 * m_roomDimensions[X] - m_source[X];
  // float source2RBY = -1 * m_roomDimensions[Y] - m_source[Y];
  // m_mirrorSources.push_back({source2RBX, source2RBY});
  //
  // float source2LBX = -1 * m_roomDimensions[X] - m_source[X];
  // float source2LBY = -1 * m_roomDimensions[Y] - m_source[Y];
  // m_mirrorSources.push_back({source2LBX, source2LBY});
  //
  //
  // //third order
  // float source3RRTX = 2 * m_roomDimensions[X] + m_source[X];
  // float source3RRTY = m_roomDimensions[Y] - m_source[Y];
  // m_mirrorSources.push_back({source3RRTX, source3RRTY});
  //
  // float source3RTTX = m_roomDimensions[X] - m_source[X];
  // float source3RTTY = 2 * m_roomDimensions[Y] + m_source[Y];
  // m_mirrorSources.push_back({source3RTTX, source3RTTY});
  //
  // float source3LTTX = -m_roomDimensions[X] - m_source[X];
  // float source3LTTY = 2 * m_roomDimensions[Y] + m_source[Y];
  // m_mirrorSources.push_back({source3LTTX, source3LTTY});
  //
  // float source3LLTX = -2 * m_roomDimensions[X] + m_source[X];
  // float source3LLTY = m_roomDimensions[Y] - m_source[Y];
  // m_mirrorSources.push_back({source3LLTX, source3LLTY});
  //
  // float source3LBBX = -m_roomDimensions[X] - m_source[X];
  // float source3LBBY = -2 * m_roomDimensions[Y] + m_source[Y];
  // m_mirrorSources.push_back({source3LBBX, source3LBBY});
  //
  // float source3LLBX = -2 * m_roomDimensions[X] + m_source[X];
  // float source3LLBY = -m_roomDimensions[Y] - m_source[Y];
  // m_mirrorSources.push_back({source3LLBX, source3LLBY});
  //
  // float source3RBBX = m_roomDimensions[X] - m_source[X];
  // float source3RBBY = -2 * m_roomDimensions[Y] + m_source[Y];
  // m_mirrorSources.push_back({source3RBBX, source3RBBY});
  //
  // float source3RRBX = 2 * m_roomDimensions[X] + m_source[X];
  // float source3RRBY = -m_roomDimensions[Y] - m_source[Y];
  // m_mirrorSources.push_back({source3RRBX, source3RRBY});
  //
  // //fourth order
  // float source4RRTTX = 2 * m_roomDimensions[X] + m_source[X];
  // float source4RRTTY = 2 * m_roomDimensions[Y] + m_source[Y];
  // m_mirrorSources.push_back({source4RRTTX, source4RRTTY});
  //
  // float source4RRBBX = 2 * m_roomDimensions[X] + m_source[X];
  // float source4RRBBY = -2 * m_roomDimensions[Y] + m_source[Y];
  // m_mirrorSources.push_back({source4RRBBX, source4RRBBY});
  //
  // float source4LLBBX = -2 * m_roomDimensions[X] + m_source[X];
  // float source4LLBBY = -2 * m_roomDimensions[Y] + m_source[Y];
  // m_mirrorSources.push_back({source4LLBBX, source4LLBBY});
  //
  // float source4LLTTX = -2 * m_roomDimensions[X] + m_source[X];
  // float source4LLTTY = 2 * m_roomDimensions[Y] + m_source[Y];
  // m_mirrorSources.push_back({source4LLTTX, source4LLTTY});

  //save numMirrorSources
  m_numMirrorSources = static_cast<int>(m_mirrorSources.size());

  std::cout << "numMirrorSources: " << m_numMirrorSources << std::endl;
  // Print coordinates
  int size = m_numMirrorSources;
   std::cout << "{";
   for (int i = 0; i < size; i++)
   {
     std::cout << "{";

     for (int j = 0; j < 2; j++)
     {
       std::cout << m_mirrorSources[i][j];
       if (j==0){std::cout << ", ";}
     }

     if (i != size - 1){std::cout << "}, ";}
     else std::cout << "}";
   }
   std::cout << "}\n" << std::endl;
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

  // // Print coordinates
  //  std::cout << "{";
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
