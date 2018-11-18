#pragma once
#include <iostream>
#include <vector>

#include "structPointCoordinates.cpp"


struct Cluster {

	//Membervariablen: Ein Cluster wird definiert durch

	//Alle Punkte im Cluster
	std::vector<PointCoordinates> points_;

	//Nummer des Clusters
	int currentClusterNumber_;

	//Zentrum des Clusters zur Clustergroessenberechnung
	PointCoordinates clusterCenter_{
	clusterCenter_.x_ = 0.0,
	clusterCenter_.y_ = 0.0,
	clusterCenter_.z_ = 0.0 };

	//Groesse des Clusters
	double clusterSize_ = 0.0;
	double maxX = 0.0;
	double minX = 0.0;
	double maxY = 0.0;
	double minY = 0.0;

	//relative Groesse des Clusters zur Bildflaeche
	double relativeArea = 0.0;

	//Funktion zur Clustergroessenberechnung
	void calculateAreaAndClusterCenterAndMinMax(int imgWidth, int imgHeight) {

		//Bildgroesse
		//imgWidth = 2448;
		//imgHeight = 2048;

		//Variablen für ClusterCenterberechnung
		double sumX = 0.0;
		double sumY = 0.0;
		double sumZ = 0.0;

		//Variablen für MinMax
		double bigX = points_[0].x_;
		double smallX = points_[0].x_;
		double bigY = points_[0].y_;
		double smallY = points_[0].y_;

		for (int i = 0; i < points_.size(); i++) {

			sumX = sumX + points_[i].x_;
			sumY = sumY + points_[i].y_;
			sumZ = sumZ + points_[i].z_;

			// X
			if (points_[i].x_ > bigX) {
				bigX = points_[i].x_;
			}
			if (points_[i].x_ < smallX) {
				smallX = points_[i].x_;
			}

			// Y
			if (points_[i].y_ > bigY) {
				bigY = points_[i].y_;
			}
			if (points_[i].y_ < smallY) {
				smallY = points_[i].y_;
			}

		};


		clusterCenter_.x_ = (float) sumX / points_.size();
		clusterCenter_.y_ = (float) sumY / points_.size();
		clusterCenter_.z_ = (float) sumZ / points_.size();

		maxX = bigX;
		minX = smallX;
		maxY = bigY;
		minY = smallY;

		/*std::cout << "Das ClusterCenter von Cluster " << currentClusterNumber_ << " ist: " << clusterCenter_.x_ << "|" << clusterCenter_.y_ << "|" << clusterCenter_.z_ << " . " << std::endl;

		std::cout << "Maximum dieses Clusters in x ist " << maxX << ", und das Minimum in x ist " << minX << "." << std::endl;
		std::cout << "Maximum dieses Clusters in y ist " << maxY << ", und das Minimum in y ist " << minY << "." << std::endl;
*/
		// Flaeche der Ellipse: A = pi * radius Y * radius X
		double pi_ = 3.1415926535897932384626433832795028841971693993751058209749445923078164;
		double area;

		area = pi_ * ((bigX - smallX) / 2) * ((bigY - smallY) / 2);

		clusterSize_ = area;

		//std::cout << "Die Flaeche des Clusters " << currentClusterNumber_ << " betraegt " << clusterSize_ << " mm^2." << std::endl;

		relativeArea = clusterSize_ / (imgHeight * imgWidth);

		//std::cout << " Die relative Flaeche des Clusters zur Bildgroesse " << imgWidth << " x "<< imgHeight <<" Pixel ist" << relativeArea << "." << std::endl; 
	}

	//für SaveToFile: 
	friend std::ostream& operator << (std::ostream& o, const Cluster& singleCluster) {
		o << singleCluster.currentClusterNumber_ << "|" << singleCluster.clusterSize_ << "|" << singleCluster.maxX << "|" << singleCluster.minX << "|" << singleCluster.maxY << "|" << singleCluster.minY << std::endl;
		return o;
	}

	

};