#include "coefficientOfDetermination.h"

double coefficientOfDetermination(std::vector<PointCoordinates> points, Sphere sphere)
{
	//Berechnung Bestimmtheitsmass R^2

	double coefficientOfDetermination = 0.0;
	double upperTerm = 0.0;
	double lowerTerm = 0.0;

	//umgestellte Kugelgleichung nach z(x,y):
	for (int i = 0; i < points.size(); i++) {
		double xDiff = 0.0, yDiff = 0.0, term = 0.0;

		xDiff = points[i].x_ - sphere.center_.x_;
		yDiff = points[i].y_ - sphere.center_.y_;
		term = (sphere.radius_ * sphere.radius_) - (xDiff * xDiff) - (yDiff * yDiff);

		if (term > 0) {

			//z_xy ist Ist-Wert
			//sqrt(term) ist negativ, weil die Kugelhälfte nach oben geöffnet ist -> "Spitze" der
			//Kugel zeigt nach unten 

			double z_xy = -sqrt(term) + sphere.center_.z_;
			upperTerm = upperTerm + ((points[i].z_ - z_xy) * (points[i].z_ - z_xy));
			lowerTerm = lowerTerm + ((points[i].z_ - sphere.average_.z_) * (points[i].z_ - sphere.average_.z_));
		}
	}


	coefficientOfDetermination = 1- (upperTerm / lowerTerm);
	sphere.fitQuality_ = coefficientOfDetermination;

	return sphere.fitQuality_;
}

