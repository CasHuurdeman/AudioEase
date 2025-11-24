//
// Created by cashu on 11/11/2025.
//

#include "room.h"

#include <filesystem>
#include <iostream>


Room::Room(/*float xSize, float ySize, float zSize*/)
{
//  std::cout << "Room - constructor" << std::endl;

  // m_roomDimensions[0] = xSize;
  // m_roomDimensions[1] = ySize;
  // m_roomDimensions[2] = zSize;

  // createRoom();
  calculateMirrorSources(7);
  addReceiver(0,0,0);
}

Room::~Room()
{
//	std::cout << "Room - destructor" << std::endl;
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
  for (float& j : arrX)
  {
    for (float& k : arrY)
    {
      m_mirrorSources.push_back({j, k});
    }
  }

  //delete the m_source coordinate
  m_mirrorSources.erase(m_mirrorSources.begin());

  //save numMirrorSources
  m_numMirrorSources = static_cast<int>(m_mirrorSources.size());
}

void Room::addReceiver(float X, float Y, float Z)
{
   m_receiverVector.push_back(new Receiver(X, Y, Z));
}

void Room::removeReceiver(int receiverVectorIndex)
{
	if (receiverVectorIndex < m_receiverVector.size())
	{
		std::cout << "Room::removeReceiver; Error: This index doest exist" << std::endl;
	}

  delete m_receiverVector[receiverVectorIndex];
  m_receiverVector[receiverVectorIndex] = nullptr;
	m_receiverVector.erase(m_receiverVector.begin() + receiverVectorIndex);
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
