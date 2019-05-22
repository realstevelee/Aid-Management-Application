// Workshop <Milestone 05>
// Name: <Sooyong Lee>
// Student #: <146074174>
// Course: OOP244 Winter 2019
// File: <AmaApp.h>
#include <iostream>
#include "iProduct.h"
#include "Utilities.h"


#ifndef AMA_APP_H
#define AMA_APP_H
namespace ama {
	class AmaApp {
		char m_filename[256];
		iProduct* m_products[100];
		int m_noOfProducts;
		void pause() const;
		int menu() const;
		void loadProductRecord();
		void saveProductRecord() const;
		void listProducts() const;
		iProduct* find(const char* sku) const;
		void addQty(iProduct* product);
		void addProduct(char tag);

	public:
		AmaApp(const char*);
		~AmaApp();
		int run();
	};
}
#endif