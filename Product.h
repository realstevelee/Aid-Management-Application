// Workshop <Milestone 05>
// Name: <Sooyong Lee>
// Student #: <146074174>
// Course: OOP244 Winter 2019
// File: <Product.h>

#include <iostream>
#include "ErrorState.h"
#include "iProduct.h"

#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H

namespace ama {
	class Product : public ErrorState, public iProduct {
		char typeProduct;
		char skuProduct[max_length_sku + 1];
		char unitProduct[max_length_unit + 1];
		char* nameProduct;
		int qtyProductHand;
		int qtyProductNeed;
		double priceProduct;
		bool taxAvailable;
		ErrorState errProduct;
	protected:
		void message(const char*);
		bool isClear() const;
	public:
		Product(char _typeProduct = 'N');
		Product(const char* _skuProduct, const char* _nameProduct, const char* _unitProduct, double _priceProduct = 0.0, int _qtyProductNeed = 0, int _qtyProductHand = 0, bool _taxAvailble = true);
		Product(const Product&);
		~Product();
		Product& operator=(const Product&);
		const char* nameAvailable() const;
		int operator+=(int cnt);
		bool operator==(const char* sku) const;
		bool operator>(const char* sku) const;
		bool operator>(const iProduct& other) const;
		int qtyAvailable() const;
		int qtyNeeded() const;
		double total_cost() const;
		bool isEmpty() const;
		const char* name() const;

		std::istream& read(std::istream& in, bool interractive);
		std::ostream& write(std::ostream& out, int writeMode) const;
	};
}

#endif