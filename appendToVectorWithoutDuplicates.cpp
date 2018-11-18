#include "appendToVectorWithoutDuplicates.h"

//Elemente an ein vorhandenes Array anh�ngen
//void == es gibt kein Return, die Funktion "macht" und "�ndert" nur an vorhandenen Variablen
//Call-by bzw. Referenz -> mit dem &!   --> �nderungen wirken sich auf die urspr�nglichen Werte/Variablen aus. Bei Call by value (also normal schreiben) wird eine Kopie erzeugt,
//Hier wird die urspr�ngliche Variable ver�ndert, also v1 


/*wenn du jetzt eine gro�e klasse (eine, die viel speicher verbraucht bzw. viele attribute hat) by value �bergibst, wird die klasse bit f�r bit kopiert. 
Wenn du sie aber by reference �bergibst, wird der funktion gesagt, _an welcher Stelle_ im arbeitsspeicher das bereits existierende objekt ist. Dadurch spart 
man die ganze Kopiererei und bei gro�en Objekten geht es schneller.
Da beim call by value nur eine Kopie des Objektes �bergeben wird, bringt es wenig, wenn die Funktion sachen an dem Objekt �ndert, da sie lediglich auf _eine Kopie_ 
des Objektes zugreift. Wenn du also eine funktion schreibst, die objekte ver�ndern soll, solltest du call-by-reference (oder �bergabe �ber pointer, aber 
das bringt h�ufig keine weiteren vorteile und macht es nur komplizierter) verwenden.*/

/* wenn der Punkt zum Vektor hinzugef�gt wird, dann muss im originalVektor (in dem Fall als v3 gekennzeichnet) der Punkt als already visited markiert werden */

void appendToVectorWithoutDuplicates(std::vector<int>& v1, std::vector<int> v2){
	for (int i = 0; i < v2.size(); i++) {

		bool pointIsInVector = vectorContainsNumber(v1, v2[i]);

		if (pointIsInVector == false) {
		
			v1.push_back(v2[i]);
			//std::cout << "Der Punkt " << v3[v2[i]].x_ << "|" << v3[v2[i]].y_ << "|" << v3[v2[i]].z_ <<" an der Stelle " << v2[i] << " wird zu den vorhandenen Punkten hinzugefuegt" << std::endl;

		}
	}

}
