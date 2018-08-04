/*
Final Project - Milestone 5
Perishable.h
Name: Crystal Ding
Section : AB
Student ID : 100414176
Date : 04 / 10 / 2018
Comment: Declare namespace AMA and define the Perishable class
*/

#ifndef AMA_PERISHABLE_H
#define AMA_PERISHABLE_H

#include "Product.h"
#include "Date.h"

namespace AMA {

	class Perishable : public Product {

		Date expiryDate;

	public:
		Perishable();
		std::fstream& store(std::fstream&, bool = true) const;
		std::fstream& load(std::fstream&);
		std::ostream& write(std::ostream&, bool) const;
		std::istream& read(std::istream& );
		const Date& expiry() const;
	};
}

#endif