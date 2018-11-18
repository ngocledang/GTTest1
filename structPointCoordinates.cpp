#pragma once
#include <iostream>
#include <cmath>

struct PointCoordinates {
	//Hat 3 interne Variablen
	float x_, y_, z_;
	bool alreadyVisited = false;
	//-1 = unbesucht
	// 0 = noise
	// >= 1 = Clusternummer
	int clusterNumber = -1;

	//Unterfunktion =  auch Methode genannt 
	//zur Bestimmung des Abstandes zwischen zwei Punkten = Betrag eines Vektors!
	//static = ist quasi eine Variable, die zugehörig zum Struct allgemein ist und nicht eine konkrete Variable wie XYZ
	static double distanceTo(struct PointCoordinates point1, struct PointCoordinates point2) { 
		//return (point1.x_ - point2.x_) * (point1.x_ - point2.x_) + (point1.y_ - point2.y_) * (point1.y_ - point2.y_);
		//return sqrt(((point1.x_ - point2.x_) * (point1.x_ - point2.x_)) + ((point1.y_ - point2.y_) * (point1.y_ - point2.y_)));

		return sqrt(((point1.x_ - point2.x_) * (point1.x_ - point2.x_)) + ((point1.y_ - point2.y_) * (point1.y_ - point2.y_)) + ((point1.z_ - point2.z_) * (point1.z_ - point2.z_)));
	}

	//für SaveToFile: 
	friend std::ostream& operator << (std::ostream& o, const PointCoordinates& v) {
		o << v.x_ << "|" << v.y_ << "|" << v.z_ << "|" << v.clusterNumber << std::endl;
		return o;
	}
};
/*
//was passiert, wenn ich den Datentyp "pointCoordinates" ins coutt werfe
friend std::ostream& operator<< (std::ostream& o, const pointCoordinates& pCoordinates) {
o << pointCoordinates.x_
}
*/