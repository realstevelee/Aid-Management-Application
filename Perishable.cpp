// Workshop <Milestone 05>
// Name: <Sooyong Lee>
// Student #: <146074174>
// Course: OOP244 Winter 2019
// File: <Perishable.cpp>
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Perishable.h"


namespace ama {
	Perishable::Perishable() : Product('P') {
		
	}

	std::ostream& Perishable::write(std::ostream& out, int writeMode) const {
		Product::write(out, writeMode);
		if (!isEmpty() && isClear()) {
			if (writeMode == write_human) {
				out << setw(max_length_label) << right << "Expiry Date: " << expDate << endl;
			}
			else if (writeMode == write_table) {
				out << " " << expDate << " |";
			}
			else if (writeMode == write_condensed) {
				out << "," << expDate;
			}
		}

		return out;
	}

	std::istream& Perishable::read(std::istream& in, bool interactive) {
		in.clear();
		Product::read(in, interactive);

		if (interactive) {
			cout << setw(max_length_label) << right << "Expiry date (YYYY/MM/DD): ";
			in >> expDate;

			if (expDate.status() != 0) {
				in.setstate(std::ios::failbit);
				if (expDate.status() == 1)
					message("Invalid Year in Date Entry");
				else if (expDate.status() == 2)
					message("Invalid Month in Date Entry");
				else if (expDate.status() == 3)
					message("Invalid Day in Date Entry");
				else
					message("Invalid Date Entry");
			}
		}
		else {
			expDate.read(in);
			in.ignore(2000, '\n');
		}

		return in;
	}
}