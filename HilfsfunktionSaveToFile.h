#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "structPointCoordinates.cpp"
#include "structCluster.cpp"
#include "structSphere.cpp"

void saveToFile(std::string filename, std::vector<PointCoordinates> v, int wait);

void saveToFileForPresentation(std::string filename, std::vector<Cluster> allClusters, int wait);

void saveToFileSphere(std::string filename, std::vector<Sphere> v, int wait);
