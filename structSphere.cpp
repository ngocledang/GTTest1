#pragma once
#include <vector>
#include "structPointCoordinates.cpp"

struct Sphere {
	PointCoordinates center_, average_;
	double radius_;
	double fitQuality_;
	//f�r SaveToFile: 
	friend std::ostream& operator<< (std::ostream& o, const Sphere& v) {
		o << v.center_.x_ << "|" << v.center_.y_ << "|" << v.center_.z_ << "|" << v.radius_ << "|" << v.fitQuality_<< std::endl;
		return o;
	}
};