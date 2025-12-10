//
// Created by cashu on 11/11/2025.
//

#include "room.h"

#include <filesystem>
#include <iostream>
#include "calculateDistance.h"

Room::Room() {
  std::cout << "Room - constructor" << std::endl;

  int diagonalOrder = 40;
  calculateMirrorSources(diagonalOrder);
  calculateMaxDistance(diagonalOrder);
}

Room::~Room()
{
	std::cout << "Room - destructor" << std::endl;
}

//TODO - a lot of this might need a process fuction
void Room::prepareReceivers(int numChannels)
{
  addReceiver(0.0f, 0.0f, 1.7f);
  addReceiver(0.2f, 0.0f, 1.7f);

//TODO - for later
  // for (int channel = 0; channel < numChannels; channel++)
  // {
  //   addReceiver(0.0f, 0.0f, 0.0f);
  // }

  //calculate al reflections of all receivers
  for (Receiver* receiver : m_receiverVector)
  {
    receiver->calculateReflections(m_mirrorSources, size(m_mirrorSources), m_soundSpeed);
    receiver->calculateSourceAmplitude(m_source, size(m_source));
  }
}


void Room::calculateMirrorSources(const int diagonalOrder)
{
  //TODO - EXPLANATION!!!!!!!!!!!!!
  // TODO - 3D
  vector arrX = {m_source[X]};
  vector arrY = {m_source[Y]};
  vector arrZ = {m_source[Z]};

  //calculate the different X and Y values to be used
  int a = -1;
  for (int i = 1; i <= diagonalOrder; i++)
  {
    arrX.push_back(static_cast<float>(i) * m_roomDimensions[X] + static_cast<float>(a) * m_source[X]);
    arrX.push_back(static_cast<float>(-i) * m_roomDimensions[X] + static_cast<float>(a) * m_source[X]);

    arrY.push_back(static_cast<float>(i) * m_roomDimensions[Y] + static_cast<float>(a) * m_source[Y]);
    arrY.push_back(static_cast<float>(-i) * m_roomDimensions[Y] + static_cast<float>(a) * m_source[Y]);

    //TODO - *0.5f good? --> think
    arrY.push_back(static_cast<float>(i) * m_roomDimensions[Z] + static_cast<float>(a) * 0.5f * m_source[Z]);
    arrY.push_back(static_cast<float>(-i) * m_roomDimensions[Z] + static_cast<float>(a) * 0.5f * m_source[Z]);
    a *= -1;
  }

  //Combine all X and Y values to get the coordinates
  for (float& x : arrX)
  {
    for (float& y : arrY)
    {
      for (float& z : arrZ)
      {
         m_mirrorSources.push_back({x, y, z});
      }
    }
  }
}

void Room::calculateMaxDistance(int diagonalOrder)
{
  // calculate max distance, not very pretty but works
  float m = -(0.5f + static_cast<float>(diagonalOrder));
  float BottomLeftMirrorCorner [] = {m * m_roomDimensions[X], m * m_roomDimensions[Y],  m * m_roomDimensions[Z]};
  float TopRightCorner [] = {0.5f * m_roomDimensions[X], 0.5f * m_roomDimensions[Y], 0.5f * m_roomDimensions[Z]};
  float maxDistance = CalculateDistance::calculateDistance(TopRightCorner, BottomLeftMirrorCorner, 3, 3);

  //caclulate maxDelay
  m_maxDelay = maxDistance / m_soundSpeed * 1000;
}


void Room::removeReceiver(int receiverIndex)
{
	if (receiverIndex < m_receiverVector.size())
	{
		std::cout << "Room::removeReceiver; Error: This index doest exist" << std::endl;
	}

  delete m_receiverVector[receiverIndex];
  m_receiverVector[receiverIndex] = nullptr;
	m_receiverVector.erase(m_receiverVector.begin() + receiverIndex);
}



















//TODO - createRoom() has no need now
//
// ADD ENUM: topL = 0, topR, bottomR, bottomL,
//
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
