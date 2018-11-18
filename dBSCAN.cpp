#include "dBSCAN.h"

std::vector<Cluster> dBSCAN(std::vector<PointCoordinates>& v, double eps, int minPts)
{
	std::vector<int> pointsToCheck;
	int currentClusterNumber = 1;
	//int counter = 0;
	std::cout << "Die Anzahl der Elemente sind " << v.size() << std::endl;
	std::cout << "Ladebalken: Ein Punkt steht fuer 1 Prozent Fortschritt" << std::endl;
	for (int i = 0; i < v.size(); i++) {
		if (v.size() > 1000){
			if (i % (v.size() / 100) == 0) {
				std::cout << ".";
			}
			if (i % (v.size() / 10) == 0) {
				std::cout << std::endl;
			}
		}
		//suche den ersten Punkt, der noch nicht besucht worden ist
		if (v[i].alreadyVisited == false) {
			v[i].alreadyVisited = true;
			//suche alle Punkte, die unter dem Abstand eps liegen und füge sie der 
			//Menge zu, die geprüft wird
			pointsToCheck = getIndexesPointsUnderEps(v[i], v, eps);
			//std::cout << "Es wurden " << pointsToCheck.size() << " Punkte gefunden, die unter epsilon " << eps << " liegen" << std::endl;
			//std::cout << "Der Punkt " << v[pointsToCheck[i]].x_ << "|" << v[pointsToCheck[i]].y_ << "|" << v[pointsToCheck[i]].z_ << " an der Stelle " << i << " liegt unter epsilon" << std::endl;

			//Kontrolle, ob die Anzahl der Punkte über minPts liegen
			//in expandCluster wird für den jeweiligen Punkt die Clusterzugehörigkeit zugewiesen 
			if (pointsToCheck.size() >= minPts) {
			//	currentClusterNumber = 1 + counter;

				v[i].clusterNumber = currentClusterNumber;
				expandCluster(v, v[i], pointsToCheck, currentClusterNumber, eps, minPts);
				
				//Printtest 

			//	for (int j = 0; j < pointsToCheck.size(); j++) {
				//	std::cout << "Der Punkt " << v[pointsToCheck[j]].x_ << "|" << v[pointsToCheck[j]].y_ << "|" << v[pointsToCheck[j]].z_ << " wird in Cluster " << currentClusterNumber << " gespeichert" << std::endl;
				//}
				currentClusterNumber++;

			}
			//wenn weniger Punkte als minPts vorliegen -> als noise werten
			else{
				v[i].clusterNumber = 0;
			//	std::cout << "pointsToCheck besitzt " << pointsToCheck.size() << " Elemente und besitzt daher weniger Nachbarn als minPts " << minPts << std::endl;
			}
		}
	}

	std::vector<Cluster> allClusters; //enthaelt alle Cluster

	//Cluster werden vorab erstellt
	for (int i = 0; i < currentClusterNumber; i++) {
		Cluster cluster_i;
		cluster_i.currentClusterNumber_ = i;
		allClusters.push_back(cluster_i);

	}
	
	//Cluster werden aufgefüllt mit Punkten 
	for (int i = 0; i < v.size(); i++) {
		
		//die Clusternummer ist ja bereits im Punkt v[i] implementiert - die Clusternummer entspricht gleichzeitig der Stelle im Vektor allCluster
		allClusters[v[i].clusterNumber].points_.push_back(v[i]);
	}
	
	//Clusterzentren der Cluster und Minima und Maxima 
	for (int i = 0; i < allClusters.size(); i++) {
		if (allClusters[i].points_.size() > 0){ //wenn Noise-Cluster leer ist, stürzt das Programm sonst ab
			allClusters[i].calculateAreaAndClusterCenterAndMinMax(2448, 2048);	
		}
	}

	//saveToFileForPresentation("Histogramm.txt", allClusters, 1);

	std::cout << std::endl;
	std::cout << "Es wurden " << currentClusterNumber - 1 << " Cluster erstellt und gefunden!" << std::endl;

	return allClusters;
	
}