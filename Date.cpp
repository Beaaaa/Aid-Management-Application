/*
Final Project - Milestone 5
Date.cpp
Name: Crystal Ding
Section : AB
Student ID : 100414176
Date : 03 / 12 / 2018
Comment: Define all the functions which have been declared in Date.h
*/

#include <cstring>
#include <iomanip>
#include "Date.h"

namespace AMA {

	//Default constructor sets the current Date to a safe empty state
	Date::Date() {
		year = 0;
		month = 0;
		day = 0;
		comparator = 0;
		errState = NO_ERROR;
	}

	//3-parameters constructor checks if the receiving data is valid, then stores them or sets the errCode 
	//and also sets the current Date to a safe empty state accordingly
	Date::Date(int yr, int mm, int dd) {
		if (yr <= max_year && yr >= min_year) {
			year = yr;

			if (mm <= 12 && mm >= 1) {
				month = mm;

				if (dd <= mdays(month, year) && dd >= 1) {
					day = dd;
					comparator = year * 372 + month * 13 + day;
					errCode(NO_ERROR);
				}
				else {
					errCode(DAY_ERROR);
				}
			}
			else {
				errCode(MON_ERROR);
			}
		}
		else {
			errCode(YEAR_ERROR);
		}

		if (bad()) {
			*this = Date();
		}
	}

	// number of days in month mon_ and year year_
	int Date::mdays(int mon, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	//errCode(int) sets the errState to the receiving errorCode
	void Date::errCode(int errorCode) {
		errState = errorCode;
	}

	//notEmpty checks if the current Date is in the safe empty state
	bool Date::notEmpty(const Date& rhs) const {
		return (year != 0 && month != 0 && day != 0 && rhs.year != 0 && rhs.month != 0 && rhs.day != 0);
	}

	//operator== returns true if current Date is equivalent to reciving Date
	bool Date::operator==(const Date& rhs) const {
		return (notEmpty(rhs) && comparator == rhs.comparator);
	}

	//operator!= returns true if current Date is not equivalent to reciving Date
	bool Date::operator!=(const Date& rhs) const {
		return (notEmpty(rhs) && comparator != rhs.comparator);
	}

	//operator< returns true if current Date is more recent than reciving Date
	bool Date::operator<(const Date& rhs) const {
		return (notEmpty(rhs) && comparator < rhs.comparator);
	}

	//operator> returns true if reciving Date is more recent than current Date
	bool Date::operator>(const Date& rhs) const {
		return (notEmpty(rhs) && comparator > rhs.comparator);
	}

	//operator<= returns true if current Date is more recent than or equivalent to reciving Date
	bool Date::operator<=(const Date& rhs) const {
		return (*this < rhs || *this == rhs);
	}

	//operator>= returns true if reciving Date is more recent than or equivalent to current Date
	bool Date::operator>=(const Date& rhs) const {
		return (*this > rhs || *this == rhs);
	}

	//errCode() returns the value or errState
	int Date::errCode() const {
		return errState;
	}

	//bad returns true if the receiving data is in bad condition
	bool Date::bad() const {
		return errState != NO_ERROR;
	}

	//read checks if the receiving data is valid and store them accordingly
	std::istream& Date::read(std::istream& istr) {
		istr >> year;
		if (istr.fail()) {
			errCode(CIN_FAILED);
		}
		else if (year > max_year || year < min_year) {
			errCode(YEAR_ERROR);
		}
		istr.ignore();

		istr >> month;
		if (istr.fail()) {
			errCode(CIN_FAILED);
		}
		else if (month < 1 || month > 12) {
			errCode(MON_ERROR);
		}
		istr.ignore();

		istr >> day;
		if (istr.fail()) {
			errCode(CIN_FAILED);
		}
		else if (errState != MON_ERROR && (day > mdays(month, year) || day < 1)) {
			errCode(DAY_ERROR);
		}

		if (bad()) {
			year = 0;
			month = 0;
			day = 0;
			comparator = 0;
		}

		return istr;
	}

	//write outputs the single Date in the proper format 
	std::ostream& Date::write(std::ostream& ostr) const {
		return ostr << year << '/'
			<< std::setfill('0') << std::setw(2) << month << '/'
			<< std::setfill('0') << std::setw(2) << day;
	}

	//operator<< is the overloaded extraction operator to output objects of Date
	std::ostream& operator<<(std::ostream& os, const Date& rhs) {
		rhs.write(os);
		return os;
	}

	//operator>> is the overloaded insertion operator to input objects of Date
	std::istream& operator>>(std::istream& is, Date& rhs) {
		rhs.read(is);
		return is;
	}

	//Destructor
	Date::~Date() {};
}
