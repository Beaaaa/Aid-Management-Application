/*
Final Project - Milestone 5
Perishable.cpp
Name: Crystal Ding
Section : AB
Student ID : 100414176
Date : 04 / 10 / 2018
Comment: Define all the functions which have been declared in Perishable.h
*/

#include <iomanip>
#include "Perishable.h"

namespace AMA {

	//zero argument constructor
	Perishable::Perishable() : Product('P') { }

	//receives a reference to an fstream object and an optional bool and returns reference to 
	//the fstream object
	std::fstream& Perishable::store(std::fstream& file, bool newLine) const {
		Product::store(file, false);
		file << "," << expiryDate;
		if (newLine) {
			file << std::endl;
		}
		return file;
	}

	//receives a reference to an fstream object and returns a reference to that fstream object
	std::fstream& Perishable::load(std::fstream& file) {
		Product::load(file);
		file.ignore();
		file >> expiryDate;
		return file;
	}

	//write receives a reference to an ostream object and a bool and returns a reference to
	//the ostream object
	std::ostream& Perishable::write(std::ostream& os, bool linear) const {
		Product::write(os, linear);
		if (!isEmpty()) {
			if (linear) {
				os << std::fixed << std::setw(2) << std::setfill('0') << expiry() << std::setfill(' ');
			}
			else {
				os << std::endl << std::setw(2) << std::setfill('0') << " Expiry date: " << expiry() << std::setfill(' ');
			}
		}
		return os;
	}

	//read extracts the data fields for the current object and returns a reference to the 
	//istream object
	std::istream& Perishable::read(std::istream& is) {
		Date temp;
		Product::read(is);
		if (!isEmpty()) {
			std::cout << " Expiry date (YYYY/MM/DD): ";
			is >> temp;
			if (temp.bad()) {
				is.setstate(std::ios::failbit);
				if (temp.errCode() == CIN_FAILED) {
					message("Invalid Date Entry");
					is.ignore(2000, '\n');
				}
				else if (temp.errCode() == YEAR_ERROR) {
					message("Invalid Year in Date Entry");
					is.ignore(2000, '\n');
				}
				else if (temp.errCode() == MON_ERROR) {
					message("Invalid Month in Date Entry");
					is.ignore(2000, '\n');
				}
				else if (temp.errCode() == DAY_ERROR) {
					message("Invalid Day in Date Entry");
					is.ignore(2000, '\n');
				}
				*this = Perishable();
				return is;
			}
			else {
				expiryDate = temp;
			}
		}
		return is;
	}

	//expiry returns the expiry date for the perishable product
	const Date& Perishable::expiry() const {
		return expiryDate;
	}
}