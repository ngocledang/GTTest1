#pragma once

#include <vector>
#include "structPointCoordinates.cpp"
#include "structSphere.cpp"
#include "structCluster.cpp"
#include "coefficientOfDetermination.h"
#include "Eigen/Dense"

Sphere calculateSphereFitEigen(std::vector<PointCoordinates> points);
Sphere calculateSphereFitNew(std::vector<PointCoordinates> points);
Sphere calculateSphereFit(std::vector<PointCoordinates> points);
Sphere calculateSphereFitOld(std::vector<PointCoordinates> points);

void writeSphereFitResultToFile(std::string fileName, std::vector<Cluster> allClusters);

std::vector<double> invert3x3(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33);
