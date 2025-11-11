//
// Created by cashu on 11/11/2025.
//

#pragma once
#include <vector>
#include <array>

class Grid {
public:
    Grid();
    ~Grid();

    void calculateDistance();
    //TODO - this the way to go?
    void createWalls();

private:
  //creatig a vector with mathematical vectors in it (to serve as the reflections)
  std::vector< std::array<float, 2> > m_vectors;

  //todo - make a scalable vector out of this?
  float m_roomX = 0.0f;
  float m_roomY = 0.0f;

  //TODO - make a vector out of this and make it so that there can be multiple sources and receivers
  //these are the coordinates of the source and receiver
  float m_source[2] = {0.0f, 0.0f};
  float m_receiver[2] = {0.0f, 0.0f};

  //Do we need this?
  int m_maxOrder = 1;
};

