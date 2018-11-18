#include "expandCluster.h"

void expandCluster(std::vector<PointCoordinates>& v, PointCoordinates p, std::vector<int> pointsToCheck, int currentClusterNumber, double eps, int minPts) {

	if (p.distanceTo == p.distanceTo){}

	/*	alle Cluster zusammen (Typ Vector<PointCord.> in Vector)
		der einzelne Cluster (Typ Vector<PointCoordinates>) - weil alle Punkte ja da drin sind
		der einzelne Punkt (Typ PC)
		der Gesamtvektor, der alle Punkte enthält, auf den zugegriffen wird (mit & gekennzeichnet) -> ist v

		*/
		//Definition für die Cluster: 

	//std::vector<int> cluster; //nur Indizes werden gespeichert 
	std::vector<int> indexesInTheEpsNeighbourhoodOfP;//## Plural von "index" in Informatik/Mathematik ist indices, während
							  //indexes nicht falsch, aber eher in anderen Kontexten üblich	ist

	//v gehört jetzt zu pointsToCheck (in der form von Indizes) 
	//als Variable einstellen, weil sie sich dynamisch ändert
	int upperLimit = (int)pointsToCheck.size();

	for (int i = 0; i < upperLimit; i++) {
		if (v[pointsToCheck[i]].alreadyVisited == false) { //## Gleichheit mit == testen
			v[pointsToCheck[i]].alreadyVisited = true;
			indexesInTheEpsNeighbourhoodOfP = getIndexesPointsUnderEps(v[pointsToCheck[i]], v, eps);

			if (indexesInTheEpsNeighbourhoodOfP.size() >= minPts) {
				appendToVectorWithoutDuplicates(pointsToCheck, indexesInTheEpsNeighbourhoodOfP);
				upperLimit = (int) pointsToCheck.size();

				//std::cout << "Die Punkte wurden dem Cluster " << currentClusterNumber << " hinzugefuegt." << std::endl;

			}
			if (v[pointsToCheck[i]].clusterNumber <= 0) {
				v[pointsToCheck[i]].clusterNumber = currentClusterNumber;
			}
		}
		
	}
}
