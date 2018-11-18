#include <fstream>
#include <cmath>

#include "sphereFit.h"

Sphere calculateSphereFitEigen(std::vector<PointCoordinates> points) {
	Sphere result;
	
	/*
	Berechnung der einzelnen Terme der Gleichung - den Durchschnitt aller Punkte und die beiden Summen der Matrizen 
	*/
	//Durchschnittsvektor
	Eigen::Matrix3Xd avg(3, 1);
	//Mit Tunnelsymbol werden die Werte zugewiesen 
	avg << 0, 0, 0;
	for (int i = 0; i < points.size(); i++) {
		avg(0, 0) = avg(0, 0) + points[i].x_;
		avg(1, 0) = avg(1, 0) + points[i].y_;
		avg(2, 0) = avg(2, 0) + points[i].z_;
	}
	avg(0, 0) = avg(0, 0) / points.size();
	avg(1, 0) = avg(1, 0) / points.size();
	avg(2, 0) = avg(2, 0) / points.size();
	
	result.average_.x_ = (float)avg(0, 0);
	result.average_.y_ = (float)avg(1, 0);
	result.average_.z_ = (float)avg(2, 0);

	//Summen
	Eigen::Matrix3Xd leftSum(3, 3);
	Eigen::Matrix3Xd rightSum(3, 1);
	Eigen::Matrix3Xd distToAverage(3, 1);
	leftSum << 0, 0, 0, 0, 0, 0, 0, 0, 0;
	rightSum << 0, 0, 0;
	distToAverage << 0, 0, 0;

	
	for (int i = 0; i < points.size(); i++) {
		distToAverage(0, 0) = points[i].x_ - avg(0, 0);
		distToAverage(1, 0) = points[i].y_ - avg(1, 0);
		distToAverage(2, 0) = points[i].z_ - avg(2, 0);

		leftSum = leftSum + (distToAverage * distToAverage.transpose());
		rightSum = rightSum + (distToAverage.transpose()*distToAverage).value() * distToAverage;
	}
	//CenterVektor
	Eigen::Matrix3Xd centerVector(3, 1);
	centerVector << 0, 0, 0;
	centerVector = avg + 0.5 * leftSum.inverse() * rightSum;
	
	//Zuweisung zur Sphaere
	result.center_.x_ = (float)centerVector(0, 0);
	result.center_.y_ = (float)centerVector(1, 0);
	result.center_.z_ = (float)centerVector(2, 0);
	
	//Berechnung Radius
	double squaredRadius = 0.0;
	double averageLength = 0.0;
	for (int i = 0; i < points.size(); i++) {
		averageLength = averageLength + (points[i].x_ * points[i].x_) + (points[i].y_ * points[i].y_) + (points[i].z_ * points[i].z_);
	}

	squaredRadius = ((centerVector(0, 0) * centerVector(0, 0)) + (centerVector(1, 0) * centerVector(1, 0)) + (centerVector(2, 0) * centerVector(2, 0))) - (2 * (centerVector.transpose() * avg).value()) + (averageLength / points.size());
	result.radius_ = sqrt(squaredRadius);

	//Bestimmung der Qualitaet des Fits:
	double r_squared = 0.0; 
	r_squared = coefficientOfDetermination(points, result);
	result.fitQuality_ = r_squared;
	
	return result;
}

Sphere calculateSphereFitNew(std::vector<PointCoordinates> points)
{
	double a11 = 0.0;
	double a12 = 0.0;
	double a13 = 0.0;
	double a21 = 0.0;
	double a22 = 0.0;
	double a23 = 0.0;
	double a31 = 0.0;
	double a32 = 0.0;
	double a33 = 0.0;

	/*double b1 = 0.0;
	double b2 = 0.0;
	double b3 = 0.0;*/

	int n = (int)points.size();

	double meanX = 0.0;
	double meanY = 0.0;
	double meanZ = 0.0;

	for (PointCoordinates pc : points) {
		meanX += pc.x_;
		meanY += pc.y_;
		meanZ += pc.z_;
	}

	meanX /= (double)n;
	meanY /= (double)n;
	meanZ /= (double)n;

	double rightSum1 = 0.0;
	double rightSum2 = 0.0;
	double rightSum3 = 0.0;

	for (PointCoordinates pc : points) {

		double xDiff = pc.x_ - meanX;
		double yDiff = pc.y_ - meanY;
		double zDiff = pc.z_ - meanZ;

		double squaredSum = xDiff * xDiff + yDiff * yDiff + zDiff * zDiff;
		rightSum1 += squaredSum * xDiff;
		rightSum2 += squaredSum * yDiff;
		rightSum3 += squaredSum * zDiff;

		a11 += xDiff * xDiff;
		a12 += xDiff * yDiff;
		a13 += xDiff * zDiff;

		a21 += yDiff * xDiff;
		a22 += yDiff * yDiff;
		a23 += yDiff * zDiff;

		a31 += zDiff * xDiff;
		a32 += zDiff * yDiff;
		a33 += zDiff * zDiff;
	}

	double v1, v2, v3;
	double w11, w12, w13, w21, w22, w23, w31, w32, w33;

	v1 = rightSum1;
	v2 = rightSum2;
	v3 = rightSum3;

	std::vector<double> wMatrix = invert3x3(a11, a12, a13, a21, a22, a23, a31, a32, a33);

	// W = U^(-1)
	w11 = wMatrix[0];
	w12 = wMatrix[1];
	w13 = wMatrix[2];
	w21 = wMatrix[3];
	w22 = wMatrix[4];
	w23 = wMatrix[5];
	w31 = wMatrix[6];
	w32 = wMatrix[7];
	w33 = wMatrix[8];

	PointCoordinates center;
	double xCenter = meanX + 0.5 * ( w11 * v1 + w12 * v2 + w13 * v3);
	double yCenter = meanY + 0.5 * ( w21 * v1 + w22 * v2 + w23 * v3);
	double zCenter = meanZ + 0.5 * ( w31 * v1 + w32 * v2 + w33 * v3);

	double radius = 0.0;
	for (PointCoordinates pc : points) {
		radius += (pc.x_ - xCenter)*(pc.x_ - xCenter) + (pc.y_ - yCenter)*(pc.y_ - yCenter) + (pc.z_ - zCenter)*(pc.z_ - zCenter);
	}
	radius /= (double)n;
	radius = sqrt(radius);

	Sphere result;
	PointCoordinates centerPoint;
	centerPoint.x_ = (float)xCenter;
	centerPoint.y_ = (float)yCenter;
	centerPoint.z_ = (float)zCenter;

	result.center_ = centerPoint;
	result.radius_ = radius;

	return result;
}

//nach Matlab-Code
Sphere calculateSphereFit(std::vector<PointCoordinates> points) {

	double a11 = 0.0;
	double a12 = 0.0;
	double a13 = 0.0;
	double a21 = 0.0;
	double a22 = 0.0;
	double a23 = 0.0;
	double a31 = 0.0;
	double a32 = 0.0;
	double a33 = 0.0;

	double b1 = 0.0;
	double b2 = 0.0;
	double b3 = 0.0;

	int n = (int) points.size();

	double meanX = 0.0;
	double meanY = 0.0;
	double meanZ = 0.0;

	for (PointCoordinates pc : points) {
		meanX += pc.x_;
		meanY += pc.y_;
		meanZ += pc.z_;
	}

	meanX /= (double)n;
	meanY /= (double)n;
	meanZ /= (double)n;

	for (PointCoordinates pc : points) {

		double xDiff = pc.x_ - meanX;
		double yDiff = pc.y_ - meanY;
		double zDiff = pc.z_ - meanZ;

		a11 += pc.x_ * xDiff;
		a12 += pc.x_ * yDiff;
		a13 += pc.x_ * zDiff;

		a21 += pc.x_ * yDiff;
		a22 += pc.y_ * yDiff;
		a23 += pc.y_ * zDiff;

		a31 += pc.x_ * zDiff;
		a32 += pc.y_ * zDiff;
		a33 += pc.z_ * zDiff;

		double summedSquares = (pc.x_*pc.x_ + pc.y_*pc.y_ + pc.z_*pc.z_);
		b1 += summedSquares * xDiff;
		b2 += summedSquares * yDiff;
		b3 += summedSquares * zDiff;
	}

	a11 *= 2.0f / (double)n;
	a12 *= 2.0f / (double)n;
	a13 *= 2.0f / (double)n;
	a21 *= 2.0f / (double)n;
	a22 *= 2.0f / (double)n;
	a23 *= 2.0f / (double)n;
	a31 *= 2.0f / (double)n;
	a32 *= 2.0f / (double)n;
	a33 *= 2.0f / (double)n;

	b1 /= (double)n;
	b2 /= (double)n;
	b3 /= (double)n;

	double v1, v2, v3;
	double w11, w12, w13, w21, w22, w23, w31, w32, w33;

	// v = A^t * b
	v1 = b1;
	v2 = b2;
	v3 = b3;

	std::vector<double> wMatrix = invert3x3(a11,a12,a13,a21,a22,a23,a31,a32,a33);

	// W = U^(-1)
	w11 = wMatrix[0];
	w12 = wMatrix[1];
	w13 = wMatrix[2];
	w21 = wMatrix[3];
	w22 = wMatrix[4];
	w23 = wMatrix[5];
	w31 = wMatrix[6];
	w32 = wMatrix[7];
	w33 = wMatrix[8];

	PointCoordinates center;
	double xCenter = w11 * v1 + w12 * v2 + w13 * v3;
	double yCenter = w21 * v1 + w22 * v2 + w23 * v3;
	double zCenter = w31 * v1 + w32 * v2 + w33 * v3;

	double radius = 0.0;
	for (PointCoordinates pc : points) {
		radius += (pc.x_ - xCenter)*(pc.x_ - xCenter) + (pc.y_ - yCenter)*(pc.y_ - yCenter) + (pc.z_ - zCenter)*(pc.z_ - zCenter);
	}
	radius /= (double)n;
	radius = sqrt(radius);

	Sphere result;
	PointCoordinates centerPoint;
	centerPoint.x_ = (float)xCenter;
	centerPoint.y_ = (float)yCenter;
	centerPoint.z_ = (float)zCenter;

	result.center_ = centerPoint;
	result.radius_ = radius;

	return result;
}


void writeSphereFitResultToFile(std::string filename, std::vector<Cluster> allClusters) {
	std::ofstream file(filename);
	if (allClusters.size() > 1){
		for (int i = 1; i < allClusters.size(); i++) {

			Sphere s = calculateSphereFit(allClusters[i].points_);
			file << s;

		}
		std::cout << "Kugel-Fitting-Ergebnis in " << filename.c_str() << " geschrieben." << std::endl;
	}
	else {
		std::cout << "Kein Kugelfitting gespeichert, da nur Noise erkannt wurde." << std::endl;
	}
}
// nach dem PDF von Jensson Engineering (unbenutzt)
Sphere calculateSphereFitOld(std::vector<PointCoordinates> points){

	double a11 = 0.0;
	double a12 = 0.0;
	double a13 = 0.0;
	double a21 = 0.0;
	double a22 = 0.0;
	double a23 = 0.0;
	double a31 = 0.0;
	double a32 = 0.0;
	double a33 = 0.0;

	double b1 = 0.0;
	double b2 = 0.0;
	double b3 = 0.0;

	int n = (int)points.size();

	double meanX = 0.0;
	double meanY = 0.0;
	double meanZ = 0.0;

	for (PointCoordinates pc : points) {
		meanX += pc.x_;
		meanY += pc.y_;
		meanZ += pc.z_;
	}

	meanX /= (double) n;
	meanY /= (double) n;
	meanZ /= (double) n;

	for (PointCoordinates pc : points) {

		double xDiff = pc.x_ - meanX;
		double yDiff = pc.y_ - meanY;
		double zDiff = pc.z_ - meanZ;

		a11 += pc.x_ * xDiff;
		a12 += pc.x_ * yDiff;
		a13 += pc.x_ * zDiff;

		a21 += pc.y_ * xDiff;
		a22 += pc.y_ * yDiff;
		a23 += pc.y_ * zDiff;

		a31 += pc.z_ * xDiff;
		a32 += pc.z_ * yDiff;
		a33 += pc.z_ * zDiff;

		double summedSquares = (pc.x_*pc.x_ + pc.y_*pc.y_ + pc.z_*pc.z_);
		b1 += summedSquares * xDiff;
		b2 += summedSquares * yDiff;
		b3 += summedSquares * zDiff;
	}

	a11 *= 2.0f / (double)n;
	a12 *= 2.0f / (double)n;
	a13 *= 2.0f / (double)n;
	a21 *= 2.0f / (double)n;
	a22 *= 2.0f / (double)n;
	a23 *= 2.0f / (double)n;
	a31 *= 2.0f / (double)n;
	a32 *= 2.0f / (double)n;
	a33 *= 2.0f / (double)n;

	b1 /= (double) n;
	b2 /= (double) n;
	b3 /= (double) n;

	double u11, u12, u13, u21, u22, u23, u31, u32, u33;
	double v1, v2, v3;
	double w11, w12, w13, w21, w22, w23, w31, w32, w33;

	// U = A^t * A
	u11 = a11 * a11 + a21 * a21 + a31 * a31;
	u12 = a11 * a12 + a21 * a22 + a31 * a32;
	u13 = a11 * a13 + a21 * a23 + a31 * a33;
	u21 = a12 * a11 + a22 * a21 + a32 * a31;
	u22 = a12 * a12 + a22 * a22 + a32 * a32;
	u23 = a12 * a13 + a22 * a23 + a32 * a33;
	u31 = a13 * a11 + a23 * a21 + a33 * a31;
	u32 = a13 * a12 + a23 * a22 + a33 * a32;
	u33 = a13 * a13 + a23 * a23 + a33 * a33;

	// v = A^t * b
	v1 = a11 * b1 + a21 * b2 + a31 * b3;
	v2 = a12 * b1 + a22 * b2 + a32 * b3;
	v3 = a13 * b1 + a23 * b2 + a33 * b3;

	std::vector<double> wMatrix = invert3x3(u11, u12, u13, u21, u22, u23, u31, u32, u33);

	// W = U^(-1)
	w11 = wMatrix[0];
	w12 = wMatrix[1];
	w13 = wMatrix[2];
	w21 = wMatrix[3];
	w22 = wMatrix[4];
	w23 = wMatrix[5];
	w31 = wMatrix[6];
	w32 = wMatrix[7];
	w33 = wMatrix[8];
	
	PointCoordinates center;
	double xCenter = w11 * v1 + w12 * v2 + w13 * v3;
	double yCenter = w21 * v1 + w22 * v2 + w23 * v3;
	double zCenter = w31 * v1 + w32 * v2 + w33 * v3;

	double radius = 0.0;
	for (PointCoordinates pc : points) {
		radius += (pc.x_ - xCenter)*(pc.x_ - xCenter) + (pc.y_ - yCenter)*(pc.y_ - yCenter) + (pc.z_ - zCenter)*(pc.z_ - zCenter);
	}
	radius /= (double) n;
	radius = sqrt(radius);

	Sphere result;
	PointCoordinates centerPoint;
	centerPoint.x_ = (float)xCenter;
	centerPoint.y_ = (float)yCenter;
	centerPoint.z_ = (float)zCenter;

	result.center_ = centerPoint;
	result.radius_ = radius;

	return result;
}

// Code zum haendischen Invertieren einer 3x3-Matrix
std::vector<double> invert3x3(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33) {
	std::vector<double> result(9, 0.0);
	double det = 
		a11 * (a22 * a33 - a32 * a23) -
		a12 * (a21 * a33 - a23 * a31) +
		a13 * (a21 * a32 - a22 * a31);

	double detInverse = 1.0f / det;

	
	result[0] = (a22 * a33 - a32 * a23) * detInverse;
	result[1] = (a13 * a32 - a12 * a33) * detInverse;
	result[2] = (a12 * a23 - a13 * a22) * detInverse;
	result[3] = (a23 * a31 - a21 * a33) * detInverse;
	result[4] = (a11 * a33 - a13 * a31) * detInverse;
	result[5] = (a21 * a13 - a11 * a23) * detInverse;
	result[6] = (a21 * a32 - a31 * a22) * detInverse;
	result[7] = (a31 * a12 - a11 * a32) * detInverse;
	result[8] = (a11 * a22 - a21 * a12) * detInverse;

	return result;
}
