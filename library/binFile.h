//
// Created by cashu on 05/12/2025.
//

#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

typedef int T;
class BinFile
{
public:
  BinFile(std::string fileName, std::string sourcePath){ m_file.open (sourcePath + "/" + fileName + ".dat", std::ios::binary); }
  ~BinFile(){ m_file.close(); }

  void write(float data)
  {
    m_file << data;
  }

  void read()
  {
    // Source - https://stackoverflow.com/a
    // Posted by Greg Hewgill, modified by community. See post 'Timeline' for change history
    // Retrieved 2025-12-05, License - CC BY-SA 3.0

    m_file.seekg(std::ios::end);
    auto endpos = m_file.tellg();
    m_file.seekg(std::ios::beg);
    std::cout << "endpos: " <<endpos << std::endl;
//    m_file.read(reinterpret_cast<char*>(m_data.data()), endpos);
  }

  std::vector<float>& getData(){ return m_data; }

private:
  std::fstream m_file;

  std::vector<float> m_data;
};