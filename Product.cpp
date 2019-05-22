// Workshop <Milestone 05>
// Name: <Sooyong Lee>
// Student #: <146074174>
// Course: OOP244 Winter 2019
// File: <Product.cpp>

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Product.h"

using namespace std;

namespace ama {
	Product::Product(char _typeProduct) : typeProduct(_typeProduct) {
		skuProduct[0] = '\0';
		unitProduct[0] = '\0';
		nameProduct = nullptr;
		qtyProductHand = 0;
		qtyProductNeed = 0;
		priceProduct = 0.0;
		taxAvailable = true;
	}

	Product::Product(const char* _skuProduct, const char* _nameProduct, const char* _unitProduct, double _priceProduct, int _qtyProductNeed, int _qtyProductHand, bool _taxAvailble) {
		strncpy(skuProduct, _skuProduct, max_length_sku);
		skuProduct[max_length_sku] = '\0';
		strncpy(unitProduct, _unitProduct, max_length_unit);
		unitProduct[max_length_unit] = '\0';

		if (max_length_name > 0) {
			nameProduct = new char[max_length_name];
			for (int i = 0; i < max_length_name; i++)
				nameProduct[i] = _nameProduct[i];
		}
		else
			nameProduct = nullptr;

		qtyProductHand = _qtyProductHand;
		qtyProductNeed = _qtyProductNeed;
		priceProduct = _priceProduct;
		taxAvailable = _taxAvailble;
	}
	const char* Product::nameAvailable() const {
		if (nameProduct[0] == '\0' || nameProduct == nullptr)
			return nullptr;
		else
			return nameProduct;
	}

	Product::Product(const Product& prod) : typeProduct('N') {
		strncpy(skuProduct, prod.skuProduct, max_length_sku);
		skuProduct[max_length_sku] = '\0';
		strncpy(unitProduct, prod.unitProduct, max_length_unit);
		unitProduct[max_length_unit] = '\0';
		strncpy(nameProduct, prod.nameProduct, max_length_name);
		nameProduct[max_length_name] = '\0';

		qtyProductHand = prod.qtyProductHand;
		qtyProductNeed = prod.qtyProductNeed;
		priceProduct = prod.priceProduct;
		taxAvailable = prod.taxAvailable;
		errProduct.message(prod.errProduct.message());


		/*if (prod.nameProduct != nullptr) {
			nameProduct = new char[max_length_name];
			for (int i = 0; i < max_length_name; i++)
				nameProduct[i] = prod.nameProduct[i];
		}
		else
			nameProduct = nullptr;*/
	}

	Product::~Product() {
		delete[] nameProduct;
	}

	Product& Product::operator=(const Product& prod) {
		if (this != &prod) {
			strncpy(skuProduct, prod.skuProduct, max_length_sku);
			skuProduct[max_length_sku] = '\0';
			strncpy(unitProduct, prod.unitProduct, max_length_unit);
			unitProduct[max_length_unit] = '\0';
			strncpy(nameProduct, prod.nameProduct, max_length_name);
			nameProduct[max_length_name] = '\0';

			qtyProductHand = prod.qtyProductHand;
			qtyProductNeed = prod.qtyProductNeed;
			priceProduct = prod.priceProduct;
			taxAvailable = prod.taxAvailable;
			errProduct.message(prod.errProduct.message());

			/*delete[] nameProduct;
			if (prod.nameProduct != nullptr) {
				nameProduct = new char[max_length_name];
				for (int i = 0; i < max_length_name; i++)
					nameProduct[i] = prod.nameProduct[i];
			}
			else
				nameProduct = nullptr;*/
		}

		return *this;
	}

	int Product::operator+=(int cnt) {
		if (cnt > 0)
			qtyProductHand += cnt;
		else
			qtyProductHand = qtyProductHand;

		return qtyProductHand;
	}

	bool Product::operator==(const char* sku) const {
		bool valid;
		if (strcmp(skuProduct, sku) == 0)
			valid = true;
		else
			valid = false;

		return valid;
	}

	bool Product::operator>(const char* sku) const {
		bool valid;
		if (strcmp(skuProduct, sku) > 0)
			valid = true;
		else
			valid = false;

		return valid;
	}

	bool Product::operator>(const iProduct& prod) const {
		bool valid;
		if (strcmp(nameProduct, prod.name()) > 0)
			valid = true;
		else
			valid = false;

		return valid;
	}

	int Product::qtyAvailable() const {
		return qtyProductHand;
	}
	int Product::qtyNeeded() const {
		return qtyProductNeed;
	}

	double Product::total_cost() const {
		double price;
		if (taxAvailable)
			price = priceProduct + priceProduct * tax_rate;
		else
			price = priceProduct;

		return static_cast<double>(qtyProductHand*price);
	}

	bool Product::isEmpty() const {
		bool valid;
		if (nameProduct == nullptr)
			valid = true;
		else
			valid = false;

		return valid;
	}

	std::istream& Product::read(std::istream& in, bool interractive) {
		if (interractive) {
			char label[max_length_label];

			cout.setf(ios::right);
			cout.width(max_length_label);

			cout << "Sku: ";
			//in.getline(skuProduct, max_length_sku);
			in >> skuProduct;
			cout.width(max_length_label);

			cout << "Name (no spaces): ";
			delete[] nameProduct;
			nameProduct = new char[max_length_name];
			//in.getline(nameProduct, max_length_name);
			in >> nameProduct;
			cout.width(max_length_label);

			cout << "Unit: ";
			//in.getline(unitProduct, max_length_unit);
			in >> unitProduct;
			cout.width(max_length_label);

			cout << "Taxed? (y/n): ";
			in >> label;

			if (label[0] == 'y' || label[0] == 'Y') {
				taxAvailable = true;
			}
			else if (label[0] == 'n' || label[0] == 'N') {
				taxAvailable = false;
			}

			if (label[0] != 'Y' && label[0] != 'y' && label[0] != 'N' && label[0] != 'n') {
				in.setstate(ios::failbit);
				message("Only (Y)es or (N)o are acceptable!");
			}
			else {
				cout.width(max_length_label);
				cout << "Price: ";
				in >> priceProduct;

				if (priceProduct <= 0.0) {
					in.setstate(ios::failbit);
					message("Invalid Price Entry!");
				}
				else {
					cout.width(max_length_label);
					cout << "Quantity on hand: ";
					in >> qtyProductHand;
					if (qtyAvailable() <= 0) {
						in.setstate(ios::failbit);
						message("Invalid Quantity Available Entry!");
					}
					else {
						cout.width(max_length_label);
						cout << "Quantity needed: ";
						in >> qtyProductNeed;
						if (qtyNeeded() <= 0) {
							in.setstate(ios::failbit);
							message("Invalid Quantity Needed Entry!");
						}
					}
				}
			}
		}
		else {
			in.getline(skuProduct, max_length_sku, ',');
			nameProduct = new char[max_length_name];
			in.getline(nameProduct, max_length_name, ',');
			in.getline(unitProduct, max_length_unit, ',');
			in >> priceProduct;
			in.ignore();
			in >> taxAvailable;
			in.ignore();
			in >> qtyProductHand;
			in.ignore();
			in >> qtyProductNeed;
		}
		in.ignore();
		return in;
	}

	std::ostream& Product::write(std::ostream& out, int writeMode) const {
		if (!isClear()) {
			out << errProduct.message();
		}
		else if (isEmpty()) {

		}
		else if (writeMode == write_table) {
			out << " ";
			out.width(max_length_sku);
			out.setf(ios::right);
			out << skuProduct << " | ";
			out.unsetf(ios::right);
			out.setf(ios::left);

			if (strlen(nameProduct) > 16) {
				for (int i = 0; i < 13; i++) {
					out << nameProduct[i];
				}
				out << "..." << " | ";
			}
			else {
				out.width(16);
				out << nameProduct << " | ";
			}

			out.unsetf(ios::left);
			out.width(10);
			out.setf(ios::left);
			out << unitProduct << " | ";
			out.unsetf(ios::left);
			out.width(7);
			out.setf(ios::right);
			out << std::fixed;
			out.precision(2);
			out << priceProduct << " | ";
			out.unsetf(ios::right);
			out.width(3);
			out.setf(ios::right);

			if (taxAvailable)
				out << "yes" << " | ";
			else
				out << "no" << " | ";

			out.unsetf(ios::right);
			out.width(6);
			out.setf(ios::right);
			out << qtyProductHand << " | ";
			out.unsetf(ios::right);
			out.width(6);
			out.setf(ios::right);
			out << qtyProductNeed << " |";
		}
		else if (writeMode == write_human) {
			out.width(max_length_label);
			out.setf(ios::right);
			out << "Sku: " << skuProduct << endl;
			out.width(max_length_label);
			out.setf(ios::right);
			out << "Name: " << nameProduct << endl;
			out.width(max_length_label);
			out.setf(ios::right);
			out.setf(ios::fixed);
			out.precision(2);
			out << "Price: " << priceProduct << endl;
			if (taxAvailable) {
				out.width(max_length_label);
				out.setf(ios::right);
				out.setf(ios::fixed);
				out.precision(2);
				out << "Price after Tax: " << priceProduct + (priceProduct * tax_rate) << endl;
			}
			else {
				out.width(max_length_label);
				out.setf(ios::right);
				out.setf(ios::fixed);
				out.precision(2);
				out << "Price after Tax: " << priceProduct << endl;
			}
			out.width(max_length_label);
			out.setf(ios::right);
			out << "Quantity Available: " << qtyProductHand << " " << unitProduct << endl;
			out.width(max_length_label);
			out.setf(ios::right);
			out << "Quantity Needed: " << qtyProductNeed << " " << unitProduct << endl;
		}
		else if (writeMode == write_condensed) {
			out << typeProduct << "," << skuProduct << "," << nameProduct << "," << unitProduct << ","
				<< priceProduct << "," << taxAvailable << "," << qtyProductHand << "," << qtyProductNeed;
		}
		
		return out;
	}

	void Product::message(const char* err) {
		errProduct.message(err);
	}

	bool Product::isClear() const {
		bool valid;
		if (errProduct)
			valid = false;
		else
			valid = true;

		return valid;
	}

	const char* Product::name() const {
		return nameProduct;
	}
}