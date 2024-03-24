#include "file_reader.h"
#include <fstream>
#include <iostream>
#include <sstream>

FileReader::FileReader(){
    // Constructor
}

std::vector<Point> FileReader::ParseCsv(const std::string& file_path){
    std::ifstream file;

    file.open(file_path);

    if (!file.is_open()){
        std::cout << "Error: unable to open file: " << file_path << std::endl;
    }

    std::vector<Point> points;

    std::string line;

    // Skip the first line because of the header
    std::getline(file, line);

    while (std::getline(file, line)){
        std::string id, latitude, longitude;
        std::istringstream tokenStream(line);
        if (std::getline(tokenStream, id, ',') && std::getline(tokenStream, latitude, ',') && tokenStream >> longitude){
            points.emplace_back(std::stoi(id), std::stof(latitude), std::stof(longitude));
        }
    }

    file.close();

    return points;
}