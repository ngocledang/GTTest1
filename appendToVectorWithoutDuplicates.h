#pragma once
#include <iostream>
#include <vector>
#include "vectorContainsNumber.h"
#include "structPointCoordinates.cpp"

//Elemente an ein vorhandenes Array anh�ngen
//void == es gibt kein Return, die Funktion "macht" und "�ndert" nur an vorhandenen Variablen
//Call-by bzw. Referenz -> mit dem &! 
void appendToVectorWithoutDuplicates(std::vector<int>& v1, std::vector<int> v2);