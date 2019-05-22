// Workshop <Milestone 05>
// Name: <Sooyong Lee>
// Student #: <146074174>
// Course: OOP244 Winter 2019
// File: <Perishable.h>
#include <iostream>
#include "Date.h"
#include "Product.h"

#ifndef PERISHABLE_H
#define PERISHABLE_H

namespace ama {
	class Perishable : public Product {
		Date expDate;

	public:
		Perishable();
		std::istream& read(std::istream& in, bool interractive);
		std::ostream& write(std::ostream& out, int writeMode) const;
	};

}
#endif