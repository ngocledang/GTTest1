#pragma once

#include <vector>
#include "calculateDistancesEps.h"
#include "expandCluster.h"
#include "structCluster.cpp"
#include "HilfsfunktionSaveToFile.h"

std::vector<Cluster> dBSCAN(std::vector<PointCoordinates> &v, double eps, int minPts);