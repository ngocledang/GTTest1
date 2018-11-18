#pragma once
#include <iostream>
#include <vector>
#include "structPointCoordinates.cpp"

std::vector<double> calculateDistancesEps(PointCoordinates p, std::vector<PointCoordinates> v, double eps);
//Indizes der Elemente des Vektors, die unter Epsilon liegen
std::vector<int> getIndexesPointsUnderEps(PointCoordinates p, std::vector<PointCoordinates> v, double eps);


// Du musst nicht f�r jede einzelne Funktion eine eigene Header-Datei schreiben.
// Wenn die Funktionen inhaltlich zussammengeh�ren, kannst du auch mehrere Funktionsk�pfe in eine Header-Datei schreiben.
// Und die anderen cpp-Dateien machen nur ein Include dieser Header-Datei.