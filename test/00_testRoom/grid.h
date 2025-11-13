//
// Created by cashu on 11/11/2025.
//

#pragma once
#include <vector>
#include <array>

//Lets for now hardcode everything
class Grid {
public:
    Grid();
    ~Grid();

    //TODO - now all void functions, change so there is less vectors and arrays to be used
    void calculateDistance();
    void calculateMsDelay();
    void calculateMirrorSources();
    void createRoom();
    //TODO - this the way to go --> for later maybe
    void createWalls();

    float square(float value);

private:
  //creatig a vector with mathematical vectors in it (to serve as the reflections)
  ///TODO - do I need this?
  std::vector< std::array<float, 2> > m_vectors;

  //List with distances receiver - mirrorSources
  std::vector<float> m_distances;
  std::vector<float> m_delayTimes;

  //todo - make a scalable vector out of this?
  float m_roomHeight = 10.0f;
  float m_roomWidth = 10.0f;
  //Array with coordinates of the corners
  std::array<std::array<float,2>,4> m_roomCorners;

  //TODO - make a vector out of this and make it so that there can be multiple sources and receivers
  //these are the coordinates (in meters) of the source and receiver
  float m_source[2] = {3.0f, 3.0f};
  std::vector< std::array<float, 2> > m_mirrorSources;
  float m_receiver[2] = {0.0f, 0.0f};

  //Do we need this?
  int m_maxOrder = 1;
};

