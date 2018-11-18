#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h> //fuer Konversion string zu float 
#include <GTEngine.h>

#include "calculateDistances.h"
#include "structPointCoordinates.cpp"
#include "structCluster.cpp"
#include "calculateDistancesEps.h"
#include "vectorContainsNumber.h"
#include "appendToVectorWithoutDuplicates.h"
#include "dBSCAN.h"
#include "HilfsfunktionSaveToFile.h"
#include "Eigen/Dense"
#include "sphereFit.h"
#include "structSphere.cpp"


int main() {
	//Definition, dass es einen Tunnel gibt zum LEsen (und dazu in Klammern gleich das File, welches in 
	// coordinates eingespeichert wird! )
	std::ifstream coordinates("PunkteBegrenzt3.txt"); //enthaelt 10.000 Punkte und nur die Kugeln
	gte::GVector<double> bss;

	//verwendete Variablen 

	std::string currentreadline;
	std::string row;
	PointCoordinates pointC;
	std::vector<PointCoordinates> pointList; //Vector, welches die Koordinaten enthält
	int countedPoints = 0;
	
	if (!coordinates.good()) {
		std::cerr << "Fehler beim Einlesen der Datei" << std::endl;
	}
	while (coordinates.good()) {
		getline(coordinates, currentreadline);


		//Vorgehensweise: Datei wird eingelesen, und jetzt muss durch die Funktion getline die einzelnen Zeilen herausgeholt werden, 
		// mit dem Delimiter "|"  und die dann vorerst in einem String eingespeichert werden, welcher dann in Float umgewandelt wird
		// und dann im Vektor vom Datentyp "pointCoordinates" eingespeichert werden kann 

		//getline läuft im Loop bis ins Unendliche (im schlimmsten Fall zumindest) 
		// Aber im internen Vektor soll nur das gespeichert werden, was keine "leere" Zeile ist
		// -> Abfrage, "solange keine Leerzeile zu finden ist, mache" 
		if (currentreadline != "") {

			//schicke currentreadline in den stringstream 
			std::stringstream ss(currentreadline);

				std::getline(ss, row, '|');
				pointC.x_ = (float)atof(row.c_str());
				//std::cout << pointC.x_ << std::endl;

				std::getline(ss, row, '|');
				pointC.y_ = (float)atof(row.c_str());
				//std::cout << pointC.y_ << std::endl;

				std::getline(ss, row, '|');
				pointC.z_ = (float)atof(row.c_str());
				//std::cout << pointC.z_ << std::endl;
				//cout << pointC.x_ << "|" << pointC.y_ << "|" << pointC.z_ << std::endl;

				//In den Vektor pointC-Komponenten einspeichern
				pointList.push_back(pointC);

				countedPoints++;
			}
		}


	std::cout << "Die Anzahl der eingelesenen Punkte betraegt " << countedPoints << std::endl;
	
	//Test DBSCAN

	std::vector<Cluster> clusterResult = dBSCAN(pointList, 7.5, 26);
	
	// zum Beispiel vom ersten Cluster clusterResult[1] den Sphere-Fit berechnen
	std::vector<Sphere> spheres;
	for (int i = 1; i < clusterResult.size(); i++) {

	/*Sphere s = calculateSphereFit(clusterResult[i].points_);
	std::cout << "Fit: " << s << std::endl;

	s = calculateSphereFitOld(clusterResult[i].points_);
	std::cout << "Old: " << s << std::endl;

	s = calculateSphereFitNew(clusterResult[i].points_);
	std::cout << "New: " << s << std::endl;

	*/ Sphere s = calculateSphereFitEigen(clusterResult[i].points_);
		std::cout << "Eigen: " << s << std::endl;
		
		spheres.push_back(s);
	}
	// von allen Clustern das Sphere-Fitting-Ergebnis berechnen
	// und das Ergebnis in eine Datei schreiben
	// Format: (x,y,z) vom Kugelmittelpunkt, Radius

	//writeSphereFitResultToFile("SphereFitResult_PunkteBegrenzt25_eps7_5_minPts26.txt", clusterResult);


	saveToFile("ClusterResult_PunkteBegrenzt25_eps7_5_minPts26.txt", pointList, 1);
	saveToFileSphere("Spheres2.txt", spheres, 1);
	return 0;
}




	/* 

	ALTER WEG, der funktioniert, aber zu gefährlich (wegen Loopgefahr wegen "eof", falls z.B. 
	das File plötzlich kaputt geht, USB rausgezogen wird etc.

	//////////////////////////////////////////////////////////////7

	coordinates.open("PunktwolkekoordinatenDarunter.txt");
	//eof = end of file (ist ne funktion, daher dahinter die Klammer)
	//solange "coordinates noch nicht am eof angekommen" - mache bitte:
	while(!coordinates.eof()) {
		getline(coordinates, ende);

		std::cout << ende << std::endl;
	}
	coordinates.close();	
	*/



	/*easy way von stackoverflow zum Lesen des Files
	https://stackoverflow.com/questions/551082/this-code-is-meant-to-output-hello-world-but-it-outputs-0x22fed8

	*/
//rdbuf = funktion "readbuffer" -> da sind alle Sachen von coordinates drin 
//std::cout << coordinates.rdbuf() << std::endl;
