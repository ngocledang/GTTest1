#pragma once
#include <iostream>
#include <vector>
#include "structPointCoordinates.cpp"

std::vector<double> calculateDistancesEps(PointCoordinates p, std::vector<PointCoordinates> v, double eps);
//Indizes der Elemente des Vektors, die unter Epsilon liegen
std::vector<int> getIndexesPointsUnderEps(PointCoordinates p, std::vector<PointCoordinates> v, double eps);


// Du musst nicht für jede einzelne Funktion eine eigene Header-Datei schreiben.
// Wenn die Funktionen inhaltlich zussammengehören, kannst du auch mehrere Funktionsköpfe in eine Header-Datei schreiben.
// Und die anderen cpp-Dateien machen nur ein Include dieser Header-Datei.