/*
Final Project - Milestone 5
iProduct.h
Name: Crystal Ding
Section : AB
Student ID : 100414176
Date : 04 / 10 / 2018
Comment: iProduct interface
*/

#ifndef AMA_IPRODUCT_H__
#define AMA_IPRODUCT_H__

#include <iostream>
#include <fstream>

namespace AMA {
	class iProduct {
	public:
		virtual std::fstream& store(std::fstream&, bool = true) const = 0;
		virtual std::fstream& load(std::fstream&) = 0;
		virtual std::ostream& write(std::ostream&, bool) const = 0;
		virtual std::istream& read(std::istream&) = 0;
		virtual bool operator==(const char*) const = 0;
		virtual double total_cost() const = 0;
		virtual const char* name() const = 0;
		virtual void quantity(int) = 0;
		virtual int qtyNeeded() const = 0;
		virtual int quantity() const = 0;
		virtual int operator+=(int) = 0;
		virtual bool operator>(const iProduct&) const = 0;
	};

	std::ostream& operator<<(std::ostream&, const iProduct&);
	std::istream& operator >> (std::istream&, iProduct&);
	double operator+=(double&, const iProduct&);
	iProduct* CreateProduct();
	iProduct* CreatePerishable();
}

#endif