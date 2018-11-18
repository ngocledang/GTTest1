#pragma once
#include <iostream>
#include "structPointCoordinates.cpp"
#include "calculateDistancesEps.h"
#include "appendToVectorWithoutDuplicates.h"
#include "vectorContainsNumber.h"


void expandCluster(std::vector<PointCoordinates>& v, PointCoordinates p, std::vector<int> pointsToCheck, int Clusternumber, double eps, int minPts);