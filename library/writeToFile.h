//
// Created by cashu on 17/11/2025.
//

#pragma once
#include <fstream>
#include <string>

//Writes to the file "output.csv" in local map
class WriteToFile {
public:
    WriteToFile(std::string sourcePath) { file.open (sourcePath + "/output.csv"); }
    ~WriteToFile() { file.close(); }

    void writeToFile(auto data) {
        file << std::to_string(data);
        file << "\n";
    }

private:
    std::ofstream file;
};
