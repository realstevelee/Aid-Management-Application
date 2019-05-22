// Workshop <Milestone 05>
// Name: <Sooyong Lee>
// Student #: <146074174>
// Course: OOP244 Winter 2019
// File: <Utilities.h>

#include <iostream>
#include "Product.h"
#include "Perishable.h"

#ifndef UTILITIES_H
#define UTILITIES_H

using namespace std;

namespace ama {

	double& operator+=(double& total, const iProduct& prod);
	ostream& operator<<(ostream& out, const iProduct& prod);
	istream& operator>>(istream& in, iProduct& prod);

	iProduct* createInstance(char tag);
}

#endif