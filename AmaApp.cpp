// Workshop <Milestone 05>
// Name: <Sooyong Lee>
// Student #: <146074174>
// Course: OOP244 Winter 2019
// File: <AmaApp.cpp>
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <fstream>

#include "AmaApp.h"

using namespace std;

namespace ama {
	AmaApp::AmaApp(const char* _m_filename) {
		strcpy(m_filename, _m_filename);
		for (int i = 0; i < 100; i++) {
			m_products[i] = nullptr;
		}
		m_noOfProducts = 0;
		loadProductRecord();
	}

	AmaApp::~AmaApp() {
		for (int i = 0; i < 100 ; i++) {
			delete m_products[i];
			m_products[i] = nullptr;
		}
	}

	void AmaApp::pause() const {
		cout << "Press Enter to continue..." << endl << endl;
		cin.ignore(1, '\n');
	}

	int AmaApp::menu() const {
		int inputType;
		cout << "Disaster Aid Supply Management Program" << endl;
		cout << "--------------------------------------"<< endl;
		cout << "1- List products" << endl;
		cout << "2- Search product" << endl;
		cout << "3- Add non-perishable product" << endl;
		cout << "4- Add perishable product" << endl;
		cout << "5- Add to product quantity" << endl;
		cout << "6- Delete product" << endl;
		cout << "7- Sort products" << endl;
		cout << "0- Exit program" << endl;
		cout << "> ";
		cin >> inputType;
		cin.clear();

		return (inputType >= 0 && inputType <= 6 ? inputType : -1);
	}

	void AmaApp::loadProductRecord() {
		int index = 0;
		char tag;
		

		for (int i = 0; i < 100 ; i++) {
			if (m_products[i] != nullptr)
				delete m_products[i];
		}

		fstream finput(m_filename, ios::in);

		if (finput) {
			do {
				finput >> tag;
				if (finput) {
					iProduct* temp = createInstance(tag);

					if (temp != nullptr) {
						m_products[index] = temp;
						finput.get();
						temp->read(finput, false);
						index++;
					}
				}
			} while (finput);
			m_noOfProducts = index;
			finput.close();
		}
		else {
			fstream fout(m_filename, ios::out);
			fout.close();
		}
	}

	void AmaApp::saveProductRecord() const {
		ofstream foutput(m_filename);
		if (foutput.is_open()) {
			for (int i = 0; i < m_noOfProducts; i++) {
				if (m_products[i] != nullptr) {
					m_products[i]->write(foutput, write_condensed);
					foutput << endl;
				}
			}
		}
		foutput.close();
	}

	void AmaApp::listProducts() const {
		double totalCost = 0.0;

		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "| Row |     SKU | Product Name     | Unit       |   Price | Tax |   QtyA |   QtyN | Expiry     |" << endl;
		cout << "|-----|---------|------------------|------------|---------|-----|--------|--------|------------|" << endl;
		for(int i = 0 ; i < m_noOfProducts ; i++)
		{
			cout << "|";
			cout.width(4);
			cout << i + 1 << " |";
			m_products[i]->write(cout, write_table);
			cout << endl;
			totalCost += *m_products[i];
		}


		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "|";
		cout.width(83);
		cout << "Total cost of support ($): | ";
		cout.width(10);
		cout.setf(ios::right);
		cout.precision(2);
		cout.unsetf(ios::right);
		cout << totalCost << " |" << endl;
		cout << "------------------------------------------------------------------------------------------------" << endl << endl;
	}

	iProduct* AmaApp::find(const char* sku) const {
		iProduct* tempProd = nullptr;

		for (int i = 0; i < m_noOfProducts; i++) {
			if (*m_products[i] == sku) {
				tempProd = m_products[i];
				break;
			}
		}
		return tempProd;
	}

	void AmaApp::addQty(iProduct* product) {
		int no;
		product->write(cout, write_human);
		cout << endl << endl << "Please enter the number of purchased items: ";
		cin >> no;

		if (!cin.fail()) {
			if (no <= (product->qtyNeeded() - product->qtyAvailable())) {
				*product += no;
				saveProductRecord();
			}
			else {
				cout << "Too many items; only " << (product->qtyNeeded() - product->qtyAvailable()) << " is needed. Please return the extra " << (no - (product->qtyNeeded() - product->qtyAvailable())) << " items." << endl;
				*product += (product->qtyNeeded() - product->qtyAvailable());
			}
			cout << endl << "Updated!\n" << endl;
		}
		else {
			cin.clear();
			cin.ignore(2000, '\n');
			cout << "Invalid quantity value!" << endl << endl;
		}
	}

	void AmaApp::addProduct(char tag) {
		if (m_noOfProducts < 100) {
			m_products[m_noOfProducts] = createInstance(tag);
			if (m_products[m_noOfProducts] != nullptr) {
				cin >> *m_products[m_noOfProducts];

				if (cin.fail()) {
					cin.clear();
					cin.ignore(2000, '\n');

					cout << endl << *m_products[m_noOfProducts] << endl;

					delete m_products[m_noOfProducts];
					m_products[m_noOfProducts] = nullptr;
				}
				else{
					m_noOfProducts++;
					saveProductRecord();
					cout << endl << "Success!" << endl;
				}
			}
		}
	}

	int AmaApp::run() {
		int inputType;
		bool valid = true;
		iProduct* tempProd = nullptr;
		char sku[max_length_sku];

		do {
			inputType = menu();
			switch (inputType) {
			case 1:
				listProducts();
				pause();
				break;
			case 2:
				cout << "Please enter the product SKU: ";
				cin >> sku;

				tempProd = find(sku);
				if (tempProd != nullptr) {
					cout << endl;
					tempProd->write(cout, write_human);
					tempProd = nullptr;
					cout << endl;
				}
				else
					cout << endl << "No such product!" << endl;
				pause();
				break;
			case 3:
				addProduct('N');
				cout << endl;
				break;
			case 4:
				addProduct('P');
				cout << endl;
				break;
			case 5:
				cout << "Please enter the product SKU: ";
				cin >> sku;

				if (char(cin.get()) == '\n') {
					tempProd = find(sku);
					if (tempProd != nullptr) {
						cout << endl;
						addQty(tempProd);
					}
					else {
						cout << endl << "No such product!\n" << endl;
					}
				}
				else {
					cout << endl << "Invalid SKU!" << endl;
				}
				break;
			case 0:
				cout << "Goodbye!" << endl;
				valid = false;
				break;
			default:
				cout << "~~~Invalid selection, try again!~~~" << endl;
				pause();
				break;
			}
		} while (valid);

		return 0;
	}
}
