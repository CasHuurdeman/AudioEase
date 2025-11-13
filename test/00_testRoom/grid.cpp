//
// Created by cashu on 11/11/2025.
//

#include "grid.h"
#include <iostream>

Grid::Grid()
{
  createRoom();
  calculateMirrorSources();
  calculateDistance();
  calculateMsDelay();
}

Grid::~Grid()
{

}

void Grid::calculateDistance()
{
  //m_roomCorners <- deze heb ik nu helemaal niet nodig, later wil ik wel checken of ik door muren ga en door welke
  // --> kruisen van 2 lijnen
  m_mirrorSources;

  m_distances.resize(m_mirrorSources.size());
  for (int i = 0; i < m_mirrorSources.size(); i++)
  {
    m_distances[i] = sqrt(square(m_mirrorSources[i][0]) + square(m_mirrorSources[i][1]));
  }
}

void Grid::calculateMsDelay() {
  float c = 343.0f; //m/s
  float cInverse = 1.0f/343.0f;

  m_delayTimes.resize(m_distances.size());
  for (int i = 0; i < m_distances.size(); i++)
  {
    m_delayTimes[i] = m_distances[i] * cInverse * 1000;
    std::cout << "DelayTimes: " << m_delayTimes[i] << std::endl;
  }
}

//TODO - work with vectors or coordinates
void Grid::createRoom()
{
  //TODO - enums? -> topL = 0, topR = 1, bottomR = 2, bottomL = 3, x  = 0, y = 1
  //topLeft
  m_roomCorners[0] =  {-m_roomWidth/2.0f, m_roomHeight/2.0f};
  //topRight
  m_roomCorners[1] =  {m_roomWidth/2.0f, m_roomHeight/2.0f};
  //bottomRight
  m_roomCorners[2] =  {m_roomWidth/2.0f, -m_roomHeight/2.0f};
  //bottomLeft
  m_roomCorners[3] =  {-m_roomWidth/2.0f, -m_roomHeight/2.0f};

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

enum Room {
  topL = 0,
  topR,
  bottomR,
  bottomL,
  X = 0,
  Y = 0
};

void Grid::calculateMirrorSources()
{
  //s = 3,3

  float source1RX = m_roomWidth - m_source[X];
  float source1RY = m_source[1];
  std::array<float, 2> mirrorSource1R{source1RX, source1RY};

  float source1LX = -m_roomWidth - m_source[X];
  float source1LY = m_source[1];
  std::array<float, 2> mirrorSource1L{source1LX, source1LY};

  float source1TX = m_source[0];
  float source1TY = m_roomHeight - m_source[X];
  std::array<float, 2> mirrorSource1T{source1TX, source1TY};

  float source1BX = m_source[0];
  float source1BY = -m_roomHeight - m_source[X];
  std::array<float, 2> mirrorSource1B{source1BX, source1BY};

  m_mirrorSources.resize(4);
  m_mirrorSources[0] = mirrorSource1R;
  m_mirrorSources[1] = mirrorSource1L;
  m_mirrorSources[2] = mirrorSource1T;
  m_mirrorSources[3] = mirrorSource1B;

  //Print the coordinates
  std::cout << "{";
  for (int i = 0; i < 4; i++)
  {
    std::cout << "{";

    for (int j = 0; j < 2; j++)
    {
      std::cout << m_mirrorSources[i][j];
      if (j==0){std::cout << ", ";}
    }

    if (i != 3){std::cout << "}, ";}
    else std::cout << "}";
  }
  std::cout << "}" << std::endl;
}


float Grid::square(float value) {
  return value * value;
}

