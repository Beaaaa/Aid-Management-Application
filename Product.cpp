/*
Final Project - Milestone 5
Product.cpp
Name: Crystal Ding
Section : AB
Student ID : 100414176
Date : 04 / 10 / 2018
Comment: Define all the functions which have been declared in Product.h
*/

#include <cstring>
#include <string>
#include <fstream>
#include <iomanip>
#include "Product.h"

namespace AMA {

	//name receives the address of the name of the product and stores it if it's not nullptr
	void Product::name(const char* nm) {
		product_name = nullptr;
		if (nm != nullptr) {
			product_name = new char[max_name_length];
			strncpy(product_name, nm, max_name_length);
			product_name[max_name_length] = '\0';
		}
	}

	//name() returns the address of the C-style string that holds the name of the product
	const char* Product::name() const {
		return product_name;
	}

	//sku returns the address of the string that holds the sku of the product
	const char* Product::sku() const {
		return product_sku;
	}

	//unit returns the address of the string that holds the unit of the product
	const char* Product::unit() const {
		return unit_des;
	}

	//taxed returns the taxable status of the product
	bool Product::taxed() const {
		return taxable_status;
	}

	//price returns the price of a single item of the product
	double Product::price() const {
		return product_price;
	}

	//cost returns the price of a single item of the product plus any tax that applies to 
	//the product
	double Product::cost() const {
		return (product_price * (1 + tax_rate));
	}

	//message receives the address of a string holding an error message and stores it in the 
	//ErrorState object
	void Product::message(const char* errMsg) {
		product_errState.message(errMsg);
	}

	//isClear returns true if the ErrorState object is clear; false otherwise
	bool Product::isClear() const {
		return product_errState.isClear();
	}

	//zero-one argument constructor
	Product::Product(char type) {
		product_type = type;
		product_sku[0] = '\0';
		unit_des[0] = '\0';
		product_name = nullptr;
		product_on_hand = 0;
		product_needed = 0;
		product_price = 0.0;
		taxable_status = false;
	}

	//seven argument constructor
	Product::Product(const char* s, const char* nm, const char* unit, int quantity, bool taxable, double p, int needed) {
		strncpy(product_sku, s, max_sku_length);
		product_sku[max_sku_length] = '\0';
		name(nm);
		strncpy(unit_des, unit, max_unit_length);
		unit_des[max_unit_length] = '\0';
		product_on_hand = quantity;
		product_needed = needed;
		product_price = p;
		taxable_status = taxable;
	}

	//copy constructor
	Product::Product(const Product& rhs) {
		product_name = nullptr;
		*this = rhs;
	}

	//copy assignment operator
	Product& Product::operator=(const Product& rhs) {
		product_name = nullptr;
		if (this != &rhs) {
			strncpy(product_sku, rhs.product_sku, max_sku_length);
			product_sku[max_sku_length] = '\0';
			name(rhs.product_name);
			strncpy(unit_des, rhs.unit_des, max_unit_length);
			unit_des[max_unit_length] = '\0';
			product_on_hand = rhs.product_on_hand;
			product_needed = rhs.product_needed;
			product_price = rhs.product_price;
			taxable_status = rhs.taxable_status;
		}
		return *this;
	}

	//destructor
	Product::~Product() {}

	//receives a reference to an fstream object and an optional bool and returns reference to 
	//the fstream object
	std::fstream& Product::store(std::fstream& file, bool newLine) const {
		if (!isEmpty()) {
			file << product_type << "," << product_sku << "," << product_name << "," << unit_des << "," << taxable_status
				<< "," << product_price << "," << product_on_hand << "," << product_needed;

			if (newLine) {
				file << std::endl;
			}
		}
		return file;
	}

	//receives a reference to an fstream object and returns a reference to that fstream object
	std::fstream& Product::load(std::fstream& file) {
		char s[max_sku_length + 1];
		char nm[max_name_length + 1];
		char unit[max_unit_length + 1];
		int quantity, needed;
		bool taxable;
		double p;

		file.getline(s, max_sku_length, ',');
		file.getline(nm, max_name_length, ',');
		file.getline(unit, max_unit_length, ',');
		file >> taxable;
		file.ignore();
		file >> p;
		file.ignore();
		file >> quantity;
		file.ignore();
		file >> needed;

		*this = Product(s, nm, unit, quantity, taxable, p, needed);

		return file;
	}

	//write receives a reference to an ostream object and a bool and returns a reference to
	//the ostream object
	std::ostream& Product::write(std::ostream& os, bool linear) const {
		if (isEmpty()) {
			os << product_errState;
		}
		else {
			if (linear) {
				os << std::setw(max_sku_length) << std::left << sku() << "|" <<
					std::setw(20) << name() << "|";
				if (taxed()) {
					os << std::fixed << std::setw(7) << std::right << std::setprecision(2) << cost() << "|";
				}
				else {
					os << std::fixed << std::setw(7) << std::right << std::setprecision(2) << price() << "|";
				}
				os << std::setw(4) << quantity() << "|" <<
					std::setw(10) << std::left << unit() << "|" <<
					std::setw(4) << std::right << qtyNeeded() << "|";
			}
			else {
				os << " Sku: " << sku() << std::endl;
				os << " Name (no spaces): " << name() << std::endl;
				os << " Price: " << std::fixed << std::setprecision(2) << price() << std::endl;
				if (taxed()) {
					os << " Price after tax: " << cost() << std::endl;
				}
				else {
					os << " Price after tax: N/A" << std::endl;
				}
				os << " Quantity on Hand: " << quantity() << " " << unit() << std::endl;
				os << " Quantity needed: " << qtyNeeded();
			}
		}
		return os;
	}

	//read extracts the data fields for the current object and returns a reference to the 
	//istream object
	std::istream& Product::read(std::istream& is) {
		char sku_[max_sku_length + 1];
		char name_[max_name_length + 1];
		char unit_[max_unit_length + 1];
		int quantity_, qtyNeeded_;
		double price_;
		bool taxed_;
		char input;

		std::cout << " Sku: ";
		is.getline(sku_, max_sku_length + 1);
		if (is.fail()) {
			is.clear();
			is.ignore(2000, '\n');
			return is;
		}

		std::cout << " Name (no spaces): ";
		is.getline(name_, max_name_length + 1);
		if (is.fail()) {
			is.clear();
			is.ignore(2000, '\n');
			return is;
		}

		std::cout << " Unit: ";
		is.getline(unit_, max_unit_length + 1);
		if (is.fail()) {
			is.clear();
			is.ignore(2000, '\n');
			return is;
		}

		std::cout << " Taxed? (y/n): ";
		is.get(input);
		if (input == 'Y' || input == 'y') {
			taxed_ = true;
		}
		else if (input == 'N' || input == 'n') {
			taxed_ = false;
		}
		else {
			is.setstate(std::ios::failbit);
			if (is.fail()) {
				product_errState.message("Only (Y)es or (N)o are acceptable");
				is.ignore(2000, '\n');
				return is;
			}
		}
		is.ignore(2000, '\n');

		std::cout << " Price: ";
		is >> price_;
		if (is.fail()) {
			product_errState.message("Invalid Price Entry");
			is.ignore(2000, '\n');
			return is;
		}
		is.ignore(2000, '\n');

		std::cout << " Quantity on hand: ";
		is >> quantity_;
		if (is.fail()) {
			product_errState.message("Invalid Quantity Entry");
			is.ignore(2000, '\n');
			return is;
		}
		is.ignore(2000, '\n');

		std::cout << " Quantity needed: ";
		is >> qtyNeeded_;
		if (is.fail()) {
			product_errState.message("Invalid Quantity Needed Entry");
			is.ignore(2000, '\n');
			return is;
		}
		is.ignore(2000, '\n');

		*this = Product(sku_, name_, unit_, quantity_, taxed_, price_, qtyNeeded_);

		return is;
	}

	//operator== returns true if the recriving string is identical to the sku of the current 
	//object; false otherwise
	bool Product::operator==(const char* s) const {
		return (strncmp(product_sku, s, max_sku_length) == 0);
	}

	//total_cost returns the total cost of all items of the product on hand, taxes included
	double Product::total_cost() const {
		return (cost() * product_on_hand);
	}

	//quantity resets the number of units that are on hand to the number received
	void Product::quantity(int on_hand) {
		product_on_hand = on_hand;
	}

	//isEmpty returns true if the object is in a safe empty state; false otherwise
	bool Product::isEmpty() const {
		return (product_sku[0] == '\0' && unit_des[0] == '\0' && (product_name == nullptr || product_name[0] == '\0') 
			&& product_on_hand == 0 && product_needed == 0 && product_price == 0.0 && !taxable_status);
	}

	//qtyNeeded returns the number of units of the product that are needed
	int Product::qtyNeeded() const {
		return product_needed;
	}

	//quantity() returns the number of units of the product that are on hand
	int Product::quantity() const {
		return product_on_hand;
	}

	//operator> returns true if the sku of the current object is greater than the string 
	//stored at the received address; false otherwise
	bool Product::operator>(const char* s) const {
		int current_sku = std::stoi(product_sku);
		int s_sku = std::stoi(s);
		return (current_sku > s_sku);
	}

	//operator>(const iProduct&) returns true if the name of the current object is greater 
	//than the name of the referenced iProduct object; false otherwise
	bool Product::operator>(const iProduct& rhs) const {
		return (strncmp(product_name, rhs.name(), max_name_length) > 0);
	}

	//operator+=(int) returns the updated number of units on hand
	int Product::operator+=(int num_unit) {
		return product_on_hand = (num_unit > 0) ? (product_on_hand + num_unit) : product_on_hand;
	}

	//operator<< inserts a iProduct record into the ostream
	std::ostream& operator<<(std::ostream& os, const iProduct& rhs) {
		rhs.write(os, true);
		return os;
	}

	//operator>> extracts the iProduct record from the istream
	std::istream& operator>>(std::istream& is, iProduct& rhs) {
		rhs.read(is);
		return is;
	}

	//operator+= adds the total cost of the iProduct object to the double received and 
	//returns the updated double
	double operator+=(double& t, const iProduct& rhs) {
		return (rhs.total_cost() + t);
	}
}
