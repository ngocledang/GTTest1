#include "HilfsfunktionSaveToFile.h"

void saveToFile(std::string filename, std::vector<PointCoordinates> v, int wait)
{	
	// Tunnel zum Output wird angelegt 
	std::ofstream file(filename);

	for (int i = 0; i < v.size(); i++) {

		if (i % wait == 0){
			file << v[i];
		}
	}
	std::cout << "Datei mit dem Namen " << filename.c_str() << " wurde erfolgreich erstellt." << std::endl;
}

void saveToFileForPresentation(std::string filename, std::vector<Cluster> allClusters, int wait)
{
	if (wait == wait) {

	}
	std::ofstream file(filename);
	for (int i = 0; allClusters.size(); i++) {

		file << allClusters[i];

	}
	std::cout << "Eine Tabelle mit dem Namen " << filename.c_str() << " wurde erfolgreich erstellt." << std::endl;

	//in mm^2 - Angabe; <200 mm^2 sind 10 mm Kugeln, <1200 sind 38 mm Kugeln, <3000 sind 60 mm Kugeln, > 3000 sind 80 mm Kugeln 
	/*int counterLess200 = 0, counterLess1200 = 0, counterLess3000 = 0, counterBigger3000 = 0;

	for (int i = 0; i < allClusters.size(); i++) {
	if (allClusters[i].currentClusterNumber_ != 0) {
	if (allClusters[i].clusterSize_ <= 200.0) {

	counterLess200++;
	}
	else if (allClusters[i].clusterSize_ <= 1200.0) {

	counterLess1200++;
	}
	else if (allClusters[i].clusterSize_ <= 3000) {

	counterLess3000++;
	}
	else if (allClusters[i].clusterSize_ > 3000) {

	counterBigger3000++;
	}
	}
	}

	// Tunnel zum Output wird angelegt
	std::ofstream file(filename);
	file << "10 mm " << "|" << counterLess200 << "|" << std::endl;
	file << "38 mm " << "|" << counterLess1200 << "|" << std::endl;
	file << "60 mm " << "|" << counterLess3000 << "|" << std::endl;
	file << "80 mm " << "|" << counterBigger3000 << "|" << std::endl;
	*/

}

void saveToFileSphere(std::string filename, std::vector<Sphere> v, int wait)
{
	// Tunnel zum Output wird angelegt 
	std::ofstream file(filename);

	for (int i = 0; i < v.size(); i++) {

		if (i % wait == 0) {
			file << v[i];
		}
	}
	std::cout << "Datei mit dem Namen " << filename.c_str() << " wurde erfolgreich erstellt." << std::endl;
}
