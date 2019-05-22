// Workshop <Milestone 05>
// Name: <Sooyong Lee>
// Student #: <146074174>
// Course: OOP244 Winter 2019
// File: <Utilities.cpp>
#include <iostream>
#include "Utilities.h"

using namespace std;

namespace ama {
	double& operator+=(double& total, const iProduct& prod) {
		total += prod.total_cost();
		return total;
	}
	ostream& operator<<(ostream& out, const iProduct& prod) {
		return prod.write(out, write_human);
	}
	istream& operator>>(istream& in, iProduct& prod) {
		return prod.read(in, true);
	}

	iProduct* createInstance(char tag) {
		iProduct* temp = nullptr;


		if (tag == 'N' || tag == 'n') {
			temp = new Product();
		}
		else if (tag == 'P' || tag == 'p') {
			temp = new Perishable();
		}

		return temp;

	}
}