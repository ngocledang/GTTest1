#pragma once
#include <iostream>
#include <vector>
#include "vectorContainsNumber.h"
#include "structPointCoordinates.cpp"

//Elemente an ein vorhandenes Array anhängen
//void == es gibt kein Return, die Funktion "macht" und "ändert" nur an vorhandenen Variablen
//Call-by bzw. Referenz -> mit dem &! 
void appendToVectorWithoutDuplicates(std::vector<int>& v1, std::vector<int> v2);