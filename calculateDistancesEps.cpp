#pragma once
#include <iostream>
#include <vector>
#include "structPointCoordinates.cpp"
#include "calculateDistancesEps.h"

////////////////// Abstände bestimmen zwischen den Punkten und nur die merken, die unter Epsilon sind 

std::vector<double> calculateDistancesEps(PointCoordinates p, std::vector<PointCoordinates> v, double eps) {

	double distance;
	std::vector<double> distancesToOnePointUnderEps; //ist leer
	int numberOfCalcDistances = 0;
	double epsilon = eps;

	for (int i = 0; i < v.size(); i++) {
		/*
		if (p.x_ == v[i].x_, p.y_ == v[i].y_, p.z_ == v[i].z_) {
			v[i].alreadyVisited == true;
		}
		*/

		//Wenn p der gleiche Punkt ist wie aus der Menge aller Punkte, dann soll nix gemacht werden, 
		// nur wenn p ungleich den Punkt aus der Menge aller Punkte ist, dann soll was geamcht werden 
		if (v[i].alreadyVisited != true) {

			//Abstand von einem Punkt zu einem anderen
			distance = PointCoordinates::distanceTo(p, v[i]);

			if (distance < epsilon) {
				distancesToOnePointUnderEps.push_back(distance);

				//Zählen
				numberOfCalcDistances++;
			}
		}
	}
	//std::cout << "Es wurden insgesamt " << numberOfCalcDistances << " Berechnungen erstellt, wo der Abstand unter dem Epsilon liegt." << std::endl;
	//std::cout << "Anzahl der Elemente im Vektor unter Epsilon sind " << distancesToOnePointUnderEps.size() << std::endl;

	// TESTAUSGABE OB DAS RICHTIGE AUSGEGEBEN WIRD
	//for (int i = 0; i < distancesToOnePointUnderEps.size(); i++) {
	//	std::cout << distancesToOnePointUnderEps[i] << std::endl;
	//}

	
	return distancesToOnePointUnderEps; //Vector mit Inhalt von doubles wird ausgegeben
}

/////////////////// Indizes der Punkte in den Vektor speichern 

std::vector<int> getIndexesPointsUnderEps(PointCoordinates p, std::vector<PointCoordinates> v, double eps) {
	
	double distance;
	std::vector<int> indexOnePointUnderEps; //ist leer
	int numberOfCalcDistances = 0;
	
	for (int i = 0; i < v.size(); i++) {
		
		/*
		if (p.x_ == v[i].x_, p.y_ == v[i].y_, p.z_ == v[i].z_) {
			v[i].alreadyVisited == true;
		}
		*/
		if (v[i].alreadyVisited == false || true){
			//if (p.x_ != v[i].x_, p.y_ != v[i].y_, p.z_ != v[i].z_) {

			//Abstand von einem Punkt zu einem anderen
			distance = PointCoordinates::distanceTo(p, v[i]);
			//std::cout << p.x_ << '|' << p.y_ << '|' << p.z_ << " zu " << v[i].x_ << '|' << v[i].y_ << '|' << v[i].z_ << std::endl;
			//std::cout << distance << std::endl;
			//std::cout << std::endl;

			if (distance < eps) {
				indexOnePointUnderEps.push_back(i);

				//Zählen
				numberOfCalcDistances++;
			}
		}
	}
	/* std::cout << "Anzahl der Elemente im Vektor unter Epsilon sind " << indexOnePointUnderEps.size() << std::endl;


	// TESTAUSGABE OB DAS RICHTIGE AUSGEGEBEN WIRD
	for (int i = 0; i < indexOnePointUnderEps.size(); i++) {
		std::cout << indexOnePointUnderEps[i] << std::endl;
	}
	*/

	return indexOnePointUnderEps; //Vector mit Inhalt von Indizes wird ausgegeben
}
