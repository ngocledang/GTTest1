#pragma once
#include <vector>
#include <cmath>
#include "Eigen/Dense"
#include "structSphere.cpp"
#include "structPointCoordinates.cpp"

double coefficientOfDetermination(std::vector<PointCoordinates> points, Sphere sphere);