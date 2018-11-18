#pragma once
#include <iostream>
#include <vector>
#include "structPointCoordinates.cpp"
#include "calculateDistances.h"

std::vector<double> calculateDistances (PointCoordinates p, std::vector<PointCoordinates> v){
	
	double distance;
	std::vector<double> distancesToOnePoint; //ist leer
	int numberOfCalcDistances = 0;
	
	//for (double i = 0; i < v.size(); i++) {
	for (PointCoordinates laufend : v) {
		
		//Abstand von einem Punkt zu einem anderen
			distance = PointCoordinates::distanceTo(p, laufend);
			distancesToOnePoint.push_back(distance);

		//Zählen
		numberOfCalcDistances++;
	}
	/*std::cout << "Es wurden insgesamt " << numberOfCalcDistances << " Berechnungen erstellt." << std::endl;
	std::cout << "Anzahl der Elemente im Vektor sind " << distancesToOnePoint.size() << std::endl;
	*/
	for (int i = 0; i < 50; i++) {
		std::cout << distancesToOnePoint[i] << std::endl;
	}
	
	
	return distancesToOnePoint; //Vector mit Inhalt von doubles wird ausgegeben
}
