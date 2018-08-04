/*
Final Project - Milestone 5
Product.h
Name: Crystal Ding
Section : AB
Student ID : 100414176
Date : 04 / 10 / 2018
Comment: Declare namespace AMA and define the Product class
*/

#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H

#include <iostream>
#include "ErrorState.h"
#include "iProduct.h"

namespace AMA {

	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double tax_rate = 0.13;

	class Product : public iProduct {
		char product_type;
		char product_sku[max_sku_length + 1];
		char unit_des[max_unit_length + 1];
		char* product_name;
		int product_on_hand;
		int product_needed;
		double product_price;
		bool taxable_status;
		ErrorState product_errState;

	protected:
		void name(const char*);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double price() const;
		double cost() const;
		void message(const char*);
		bool isClear() const;

	public:
		Product(char = 'N');
		Product(const char*, const char*, const char*, int = 0, bool = true, double = 0.0, int = 0);
		Product(const Product&);
		Product& operator=(const Product&);
		virtual ~Product();
		std::fstream& store(std::fstream&, bool = true) const;
		std::fstream& load(std::fstream&);
		std::ostream& write(std::ostream&, bool) const;
		std::istream& read(std::istream&);
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char*) const;
		bool operator>(const iProduct&) const;
		int operator+=(int);
	};

	std::ostream& operator << (std::ostream&, const iProduct&);
	std::istream& operator >> (std::istream&, iProduct&);
	double operator+=(double&, const iProduct&);
}

#endif

