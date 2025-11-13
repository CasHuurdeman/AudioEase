//
// Created by cashu on 11/11/2025.
//

#include "grid.h"
#include <iostream>

Grid::Grid()
{
//  std::cout << "Grid - constructor" << std::endl;

  //calculate amplitude from source to receiver
  float distance = sqrt(square(m_source[0]) + square(m_source[1]));
  m_sourceAmplitude = 1 / pow(distance, 1.5f);

  createRoom();
  calculateMirrorSources();
  calculateReflections();
}

Grid::~Grid()
{
//	std::cout << "Grid - destructor" << std::endl;
}

void Grid::calculateReflections()
{
  //m_roomCorners <- deze heb ik nu helemaal niet nodig, later wil ik wel checken of ik door muren ga en door welke
  // --> kruisen van 2 lijnen

  //c = sound of speed in m/s @20 deg celcius
  float c = 343.0f;

  m_reflections.resize(m_numMirrorSources);
  for (int i = 0; i < m_numMirrorSources; i++)
  {
    //first calculate the distance receiver(@{0,0}) - mirrorSource
    float distance = sqrt(square(m_mirrorSources[i][0]) + square(m_mirrorSources[i][1]));

    //amplitude according to Richard Moore (Elements of computer music p370)
	float amplitude = 1 / pow(distance, 1.5f);
    float delayTime = distance / c * 1000;
    m_reflections[i][0] = delayTime;
    m_reflections[i][1] = amplitude;
    // std::cout << "DelayTimes: " << m_reflections[i][0] << "\nAmplitudes: " << m_reflections[i][1] << std::endl;
  }
}

enum Room
{
  topL = 0, topR, bottomR, bottomL, X = 0, Y = 0
};

//TODO - will I work with vectors or coordinates? --> I think coordinates
void Grid::createRoom()
{
  //topLeft
  m_roomCorners[topL] =  {-m_roomWidth/2.0f, m_roomHeight/2.0f};
  //topRight
  m_roomCorners[topR] =  {m_roomWidth/2.0f, m_roomHeight/2.0f};
  //bottomRight
  m_roomCorners[bottomR] =  {m_roomWidth/2.0f, -m_roomHeight/2.0f};
  //bottomLeft
  m_roomCorners[bottomL] =  {-m_roomWidth/2.0f, -m_roomHeight/2.0f};

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

void Grid::calculateMirrorSources()
{

  float source1RX = m_roomWidth - m_source[X];
  float source1RY = m_source[Y];
  std::array<float, 2> mirrorSource1R{source1RX, source1RY};

  float source1LX = -m_roomWidth - m_source[X];
  float source1LY = m_source[Y];
  std::array<float, 2> mirrorSource1L{source1LX, source1LY};

  float source1TX = m_source[X];
  float source1TY = m_roomHeight - m_source[X];
  std::array<float, 2> mirrorSource1T{source1TX, source1TY};

  float source1BX = m_source[X];
  float source1BY = -m_roomHeight - m_source[X];
  std::array<float, 2> mirrorSource1B{source1BX, source1BY};

  m_mirrorSources.resize(4);
  m_mirrorSources[0] = mirrorSource1R;
  m_mirrorSources[1] = mirrorSource1L;
  m_mirrorSources[2] = mirrorSource1T;
  m_mirrorSources[3] = mirrorSource1B;

  m_numMirrorSources = static_cast<int>(m_mirrorSources.size());
//  //Print the coordinates
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
//  std::cout << "}" << std::endl;
}


