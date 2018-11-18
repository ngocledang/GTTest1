#pragma once
#include "vectorContainsNumber.h"


//Funktion zum Anzugeben, ob der Punkt im Vektor ist oder nicht (im Vector selbst sind jedoch nur die Indizes der Punkte gespeichert -> Datentyp double 
bool vectorContainsNumber(std::vector<int> v, int k){
	

	for (int i = 0; i < v.size(); i++) {
		if (v[i] == k) {

		//	std::cout << "Der Punkt " << k << " ist bereits im Vektor." << std::endl;

			return true;
		}

	}
	//std::cout << "Der Punkt " << k << " ist noch nicht im Vektor." << std::endl;
	return false;
	
	/*
	Alternative Lösung mit for-each-Schleife
	
	for (int x : v){
		if (x == k){
			return true;
		}
	}
	return false;
	*/
}
